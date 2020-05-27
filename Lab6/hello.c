#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/printk.h>
#include <linux/errno.h>

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint how_many = 1;
module_param(how_many, uint, S_IRUGO);
MODULE_PARM_DESC(how_many, "Parameter defines how many times current string should be printed.");

struct linked_list {
	struct list_head list_node;
	ktime_t start;
	ktime_t finish;
};

static LIST_HEAD(linked_head);

static int __init hello_init(void)
{
	uint i;
	struct linked_list *data;
	ktime_t start, finish;

	WARN_ON((how_many == 0) || (how_many >= 5 && how_many <= 10));

	BUG_ON(how_many > 10);

	BUG_ON(!list_empty(&linked_head));

	for (i = 0; i < how_many; i++)
	{
		start = ktime_get();
		printk(KERN_EMERG "Hello, world!\n");
		finish = ktime_get();

		data = (struct linked_list*) kmalloc(sizeof(struct linked_list), GFP_KERNEL);

		if (i == 3)
		{
			data = NULL;
		}

		*data = (struct linked_list) {
		(struct list_head) {NULL, NULL},
		start,
		finish
		};

		list_add_tail(&data->list_node, &linked_head);
	}

	return 0;

}

EXPORT_SYMBOL(hello_init);

static void __exit hello_exit(void)
{
	struct linked_list *data, *tmp;
	list_for_each_entry_safe(data, tmp, &linked_head, list_node)
	{
 
		printk(KERN_EMERG "time=%lld\n", data->finish - data->start);
		list_del(&data->list_node);
		kfree(data);
	}
}

module_init(hello_init);
module_exit(hello_exit);
