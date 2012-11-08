#include <cos_component.h>
#include <print.h>
#include <cos_component.h>
#include <res_spec.h>
#include <sched.h>

#include <periodic_wake.h>
#include <timed_blk.h>

#include <swifi.h>

int high, low;

int fault_inject()
{
	int ret = 0;
	int tid, spdid;

	printc("\nthread %d in fault injector %ld\n\n", cos_get_thd_id(), cos_spd_id());
	
	/* make some system call cos_thd_cntl... to read/write regs */

	struct cos_regs r;

	for (tid = 1; tid <= MAX_NUM_THREADS; tid++) {
		spdid = cos_thd_cntl(COS_THD_INV_SPD, tid, 15, 0); /* ramfs spd 15 now */
		if (spdid == -1) continue;

		printc("found thd %d and spd %d\n", tid, spdid);
		cos_regs_read(tid, spdid, &r);
		cos_regs_print(&r);
		flip_all_regs(&r);
		cos_regs_print(&r);
	}
	

	return 0;
}


void cos_init(void)
{
	static int first = 0;
	union sched_param sp;
	int rand;

	if(first == 0){
		first = 1;

		sp.c.type = SCHEDP_PRIO;
		sp.c.value = 4;
		high = sched_create_thd(cos_spd_id(), sp.v, 0, 0);
	} else {
		if (cos_get_thd_id() == high) {
			periodic_wake_create(cos_spd_id(), 6);
			while(1) {
				fault_inject();
				periodic_wake_wait(cos_spd_id());
			}
		} 
	}
}