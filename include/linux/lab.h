/*
 * include/linux/lab.h
 * defines stack_info data structure
 * defines Hyper_call types nr
 * Author: xSun
 * Time: 2018-1-8
 */
#include <linux/rbtree.h>
#include <linux/kvm_types.h>
#include <linux/types.h>
#include <linux/rculist.h>

struct lab_entry {
	bool is_last_spte[4];       /* is the last level spte?*/
	u64 * eptps[4];	            /* addr of l4 ept entry which points to the target host phys page 4 frames 4 entries*/
};

struct lab_stack_info {
	pid_t pid;              	/* process pid */
	gpa_t guest_phys;	        /* stack guest physical addr */
	struct lab_entry entry;     /* entry structure */
	struct rb_node node;		/* stack info rbtree */
};

struct lab_stack_node
{
	gva_t guest_phys;           /* stack guest physical addr */ 
	pid_t pid;	                /* process pid */
	struct list_head l_node ;     /* list node */
};

/* hypercall types,intercepting event types */
#define LAB_HC_CREATE  10
#define LAB_HC_DELETE  11
#define LAB_HC_SWITCH  12
#define LAB_HC_TEST    16


/* setting permission to ept entry */
#define LAB_RO	  1
#define LAB_WT    2

extern int set_ept_entry(struct kvm_vcpu *vcpu, pid_t pid, gpa_t addr, struct lab_stack_info * data); 
extern int setting_perms(struct kvm_vcpu *vcpu, struct lab_stack_info * data, int perm);
extern bool found_in_stack_list(gva_t gpa); 

extern struct list_head stack_list;
