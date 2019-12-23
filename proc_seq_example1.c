#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/proc_fs.h>
#include<linux/slab.h>
#include<linux/seq_file.h>

static LIST_HEAD(mydrv_list);  
static struct proc_dir_entry *entry = NULL ; 

struct _mydrv_struct {
	struct list_head list;
	char info[13];
};

static void *mydrv_seq_start(struct seq_file *seq, loff_t *pos) {
	struct _mydrv_struct *p;
	loff_t off = 0;

	dump_stack(); 

	list_for_each_entry(p, &mydrv_list, list) {
		if (*pos == off++) {
			printk("In Start : Success %d\n",*pos);
            		return p;
    		}
  	}
	printk("In seq_start : Over\n");
	return NULL;
}

static void *mydrv_seq_next(struct seq_file *seq, void *v, loff_t *pos) {
	dump_stack();
	struct list_head *n = ((struct _mydrv_struct *)v)->list.next;
  	++*pos;

  	printk("in seq_next :%d\n",*pos);
  	return(n != &mydrv_list) ? list_entry(n, struct _mydrv_struct, list) : NULL;
}

static int mydrv_seq_show(struct seq_file *seq, void *v){
   int ret;
   struct _mydrv_struct  *p =v;
   dump_stack();

   printk("in seq_show \n");

   ret = seq_printf(seq,"%s\n",p->info);
   printk(KERN_INFO "the return value of seq_printf is %d\n", ret); 
   return 0;
}

static void mydrv_seq_stop(struct seq_file *seq, void *v) {
   dump_stack();
   printk("in seq_stop:\n");
}

static struct seq_operations mydrv_seq_ops = {
   .start = mydrv_seq_start,
   .next   = mydrv_seq_next,
   .stop   = mydrv_seq_stop,
   .show   = mydrv_seq_show,
};

static int mydrv_seq_open(struct inode *inode, struct file *file) {
   printk("we are in mydrv_seq_open\n");
   dump_stack();  
   return seq_open(file, &mydrv_seq_ops);
}

static struct file_operations mydrv_proc_fops = {
   .owner    = THIS_MODULE,
   .open     = mydrv_seq_open,
   .read     = seq_read,          
   .llseek   = seq_lseek,         
   .release  = seq_release,       
};

static int __init mydrv_init(void) {
   int i;
   struct _mydrv_struct *mydrv_new;
   dump_stack();

   entry1 = proc_mkdir("proc_test",  NULL);                             //a directory is created 
   entry = proc_create("readme", S_IRUSR, entry1, &mydrv_proc_fops);    //a file is created
   if (!entry) { return -EINVAL; }

   for (i=0;i<10;i++) {
        mydrv_new = kmalloc(sizeof(struct _mydrv_struct), GFP_KERNEL);
        sprintf(mydrv_new->info, "Node No: %d\n", i);
        list_add_tail(&mydrv_new->list, &mydrv_list);
   }
   printk("we are in init function of the module\n");
   return 0;
}

static void mydrv_exit(void) {
   dump_stack();
   struct _mydrv_struct *p, *n;

   list_for_each_entry_safe(p,n, &mydrv_list, list)
   {  kfree(p); }

   remove_proc_entry("readme", entry1);
   remove_proc_entry("proc_test", NULL);

   printk("mydrv_exit just executed\n");
}

module_init(mydrv_init);
module_exit(mydrv_exit);

MODULE_LICENSE("GPL v2");
