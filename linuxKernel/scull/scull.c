#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/uaccess.h>

struct scull_dev {
    struct scull_qset *data;
    int quantum;
    int qset;
    unsigned long size;
    unsigned int access_key;
    struct semahpore sem;
    struct cdev cdev;
};

static void scull_setup_cdev(struct scull_dev *dev, int index)
{
    int err, devno = MKDEV(scull_major, scull_minor + index);

    cdev_init(&dev->cdev, &scull_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &scull_fops;
    err = cdev_add(&dev->cdev, devno, 1);
    /* Fail gracefully if need be */
    if (err) {
	printk(KERN_NOTICE "Error %d adding scull %d", err, index);
    }
}


int scull_open(struct inode *inode, struct file *filp)
{
    struct scull_dev *dev;
    dev = container_of(inode->i_cdev, struct scull_dev, cdev);
    filp->private_data = dev;

    if((filp->f_flags & O_ACCMODE) == O_WRONLY) {
	scull_trim(dev);
    }
    return 0;
}

int scull_release(struct inode *inode, struct file *filp)
{
    return 0;
}


ssize_t scull_read(struct file *filep, char __user *buf, size_t count, loff_t *f_pos)
{
    struct scull_dev *dev = filp->private_data;
    struct scull_qset *dptr; 	/* the first listitem */
    int quantum, qset;
    int itemsize; 		/* how many bytes in the listitem */
    int item, s_pos, q_pos, rest;
    ssize_t retval = 0;

    if (down_interruptible(&dev->sem))
	return -ERESTARTSYS;
    quantum = dev->quantum;
    qset = dev->qset;
    itemsize = quantum*qset;

    if (*f_pos >= dev->size)
	goto out;
    if (*f_pos + count > dev->size)
	count = dev->size - *f_pos;

    /* find listitem, qset index, and offset in the quantum */
    item = (long)*f_pos / itemsize;
    rest = (long)*f_pos % itemsize;
    s_pos = rest / quantum; q_pos = rest % quantum;
    
    /* follow the list up to the right position (defined elsewhere) */
    dptr = scull_follow(dev, item);

    if (dptr == NULL || !dptr->data || !dptr->data[s_pos])
	goto out;
    *f_pos += count;
    retval = count;

    out:
    up(&dev->sem);
    return retval;
}
