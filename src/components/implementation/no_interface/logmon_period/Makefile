C_OBJS=logmon_period.o
ASM_OBJS=
COMPONENT=mon_p.o
INTERFACES=
DEPENDENCIES=periodic_wake lock sched printc mem_mgr timed_blk ll_log  

include ../../Makefile.subsubdir
ifeq (${ENABLE_STACK_MANAGER},1)
# $(info Using Simple Stack)
 MANDITORY_LIB=simple_stklib.o
endif
