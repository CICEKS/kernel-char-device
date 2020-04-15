#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Süleyman ÇİÇEK | CICEKS");
MODULE_DESCRIPTION("First Kernel Module");
MODULE_VERSION("0.0.1");

#define DEVICE_NAME     "chrDev"
#define CLASS_NAME      "chrClass"
#define BUFFER_LEN      512

static int      deviceNumber;
static char     buffer[BUFFER_LEN] = {0};
static size_t   buffer_len = 0;

static struct   class *_class = NULL;
static struct   device *_device = NULL;

static int      dev_open(struct inode *, struct file *);
static int      dev_release(struct inode *, struct file *);
static ssize_t  dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t  dev_write(struct file *, const char *, size_t, loff_t *);

static struct
        file_operations fops =
        {
                .open = dev_open,
                .read = dev_read,
                .write = dev_write,
                .release = dev_release,
        };

static int __init test_init(void)
{
        deviceNumber = register_chrdev(0, DEVICE_NAME, &fops);
        _class = class_create(THIS_MODULE, CLASS_NAME);
        _device = device_create(_class, NULL, MKDEV(deviceNumber, 0), NULL, DEVICE_NAME);

        return 0;
}

static void __exit test_exit(void)
{
        device_destroy(_class, MKDEV(deviceNumber, 0));
        class_unregister(_class);
        class_destroy(_class);
        unregister_chrdev(deviceNumber, DEVICE_NAME);
}

module_init(test_init);
module_exit(test_exit);


static int
dev_open(struct inode *inodep, struct file *filep)
{
        printk(KERN_INFO "[CICEKS] Device Opened\n");
        return 0;
}

static int
dev_release(struct inode *inodep, struct file *filep)
{
        printk(KERN_INFO"[CICEKS] Device Closed\n");
        return 0;
}

static ssize_t
dev_read(struct file *filep, char *buf, size_t size, loff_t *offset)
{
        int err = copy_to_user(buf, buffer, buffer_len);
        buffer_len = 0;
        return err;
}

static ssize_t
dev_write(struct file *filep, const char *buf, size_t size, loff_t *offset)
{
        sprintf(buffer, "%s", buf);
        buffer_len = strlen(buffer);
        return size;
}
