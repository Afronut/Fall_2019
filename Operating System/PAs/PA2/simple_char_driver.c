

#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

#define BUFFER_SIZE 1024
#define DEVICE_NAME "Coovi_Simple_Char_Device"
#define CLASS_NAME "Coovi_devices"

int DEVICE_OPEN = 0;
int Major;
char **message;
int read_dir = 0;
char *disk_space;
int Major = 300;
int read_bytes = 0;
int write_bytes = 0;
/* Define device_buffer and other global data structures you will need here */

ssize_t simple_char_driver_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
	/* length is the length of the userspace buffer*/
	/* offset will be set to current position of the opened file after read*/
	/* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */
	printk(KERN_INFO "Started reading. Buffer_length=%d, Offset=%d\n", (int)length, (int)*offset);
	if ((int)length + *offset > BUFFER_SIZE /*|| (int)length - *offset <0*/)
	{
		printk(KERN_ALERT "Reading beyond buffer size is forbidden\n");
		return -1;
	}

	printk(KERN_INFO "Reading %d to user space\n", (int)length);
	read_bytes = length - copy_to_user(buffer, disk_space + *offset, length);
	*offset += read_bytes;
	printk(KERN_INFO "Total of %d bytes copied to user space\n", read_bytes);
	printk(KERN_INFO "AFTER reading. Buffer_length=%d, Offset=%d\n", (int)length, (int)*offset);
	return 0;
}

ssize_t simple_char_driver_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
	/* length is the length of the userspace buffer*/
	/* current position of the opened file*/
	/* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */
	if ((int)length + *offset > BUFFER_SIZE /*|| *offset - (int)length  <0 */)
	{
		printk(KERN_ALERT "writing beyond buffer size is forbidden\n");
		return -1;
	}

	printk(KERN_INFO "writing to device\n");
	write_bytes = length - copy_from_user(disk_space + *offset, buffer, length);
	*offset += write_bytes;

	printk(KERN_INFO "Total of %d bytes copied from user space\n", write_bytes);

	return write_bytes;
}

int simple_char_driver_open(struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	DEVICE_OPEN++;
	printk(KERN_INFO "Device has been opened %d times\n", DEVICE_OPEN);
	return 0;
}

int simple_char_driver_close(struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	printk(KERN_INFO "closing device after %d successful open operation\n", DEVICE_OPEN);
	return 0;
}

loff_t simple_char_driver_seek(struct file *pfile, loff_t offset, int whence)
{
	/* Update open file position according to the values of offset and whence */
	loff_t new_pos = 0;
	printk(KERN_INFO "Setting offset= %d, whence=%d\n", (int)offset, whence);
	switch (whence)
	{
	case 0: /* SEEK_SET: */
		if ((int)offset > BUFFER_SIZE || (int)offset < 0)
		{
			printk(KERN_ALERT "Seeking beyond memory range is not allowed in SEEK_SET\n");
			return -1;
		}
		new_pos = offset;
		break;
	case 1: /* SEEK_CUR: */
		new_pos = pfile->f_pos + offset;
		if (new_pos > BUFFER_SIZE || new_pos < 0)
		{
			printk(KERN_ALERT "Seeking beyond file memory range is forbidden in SEEK_CUR\n");
			return -1;
		}
		break;
	case 2: /* SEEK_END: */
		new_pos = BUFFER_SIZE - offset;
		if (new_pos < 0 || new_pos > BUFFER_SIZE)
		{
			printk(KERN_ALERT "Seeking beyond file memory range is forbidden in SEEK_END\n");
			return -1;
		}
		break;
	}
	printk(KERN_INFO "current position is set to %d\n", (int)new_pos);
	pfile->f_pos = new_pos;
	return 0;
}

struct file_operations simple_char_driver_file_operations = {

	.owner = THIS_MODULE,
	.open = simple_char_driver_open,
	.llseek = simple_char_driver_seek,
	.release = simple_char_driver_close,
	.read = simple_char_driver_read,
	.write = simple_char_driver_write
	/* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
};

static int simple_char_driver_init(void)
{
	/* print to the log file that the init function is called.*/
	/* register the device */
	int er_Major = register_chrdev(300, DEVICE_NAME, &simple_char_driver_file_operations);
	if (er_Major < 0)
	{
		printk(KERN_ALERT "Unable to register device with %d major number. Consider a new major number\n", Major);
		return er_Major;
	}
	disk_space = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	if (disk_space)
		printk(KERN_INFO "Specified Buffer size of allocated successfully\n");
	else
	{
		printk(KERN_ALERT "Buffer allocation failed\n");
		return -1;
	}
	if (Major < 0)
	{
		printk(KERN_ALERT "Device Registration Failed %d\n", Major);
		return Major;
	}
	printk(KERN_INFO "Device Registration Success, Major Number is: %d\n", Major);

	return 0;
}

static void simple_char_driver_exit(void)
{
	/* print to the log file that the exit function is called.*/
	/* unregister  the device using the register_chrdev() function. */
	printk(KERN_INFO "Exiting\n");
	kfree(disk_space);
	printk(KERN_INFO "Device %s Unregister. Enjoy your wonderful time \n", DEVICE_NAME);
	unregister_chrdev(Major, DEVICE_NAME);
}

/* add module_init and module_exit to point to the corresponding init and exit function*/
module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);