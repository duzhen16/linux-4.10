/*
 * include/linux/lab.h
 * defines stack_info data structure
 * defines Hyper_call types nr
 * Author: xSun
 * Time: 2018-1-8
 */
#include <linux/kvm_types.h>
#include <linux/types.h>
#include <linux/rculist.h>

struct lab_stack_node
{
	gva_t guest_phys;           /* stack guest physical addr */ 
	pid_t pid;	                /* process pid */
	struct list_head l_node ;   /* list node */
};

/* hypercall types,intercepting event types */
#define LAB_HC_CREATE  10
#define LAB_HC_DELETE  11
#define LAB_HC_SWITCH  12
#define LAB_HC_TEST    16


/* setting permission to ept entry */
#define LAB_RO	  1
#define LAB_WT    2

extern int setting_perm_switch(struct kvm_vcpu *vcpu, gpa_t addr, int perm);
extern int setting_perm_ceate(struct kvm_vcpu *vcpu, gpa_t addr);
extern int setting_perm_delete(struct kvm_vcpu *vcpu, gpa_t addr);
extern bool found_in_stack_list(gva_t gpa); 
extern bool iterate_ept(struct kvm_vcpu *vcpu, gpa_t addr);
extern struct list_head stack_list;
