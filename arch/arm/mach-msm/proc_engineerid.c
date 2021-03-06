#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include "devices.h"

static int c_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%d\n", engineer_id);

	return 0;
}

static void *c_start(struct seq_file *m, loff_t *pos)
{
	return *pos < 1 ? (void *)1 : NULL;
}

static void *c_next(struct seq_file *m, void *v, loff_t *pos)
{
	++*pos;
	return NULL;
}

static void c_stop(struct seq_file *m, void *v)
{
}

const struct seq_operations engineerid_op = {
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= c_show
};

extern const struct seq_operations engineerid_op;
static int engineerid_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &engineerid_op);
}

static const struct file_operations proc_engineerid_operations = {
	.open		= engineerid_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= seq_release,
};

static int __init proc_engineerid_init(void)
{
	proc_create("engineerid", 0, NULL, &proc_engineerid_operations);
	return 0;
}
module_init(proc_engineerid_init);

