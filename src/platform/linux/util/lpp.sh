#!/bin/sh

./cos_loader \
"c0.o, ;llboot.o, ;*fprr.o, ;mm.o, ;print.o, ;boot.o, ;\
!l.o,a1;(!po.o=ppong.o), ;(!pi.o=pingp.o), ;!va.o,a2;!sm.o,a4;!mpool.o,a3:\
c0.o-llboot.o;\
fprr.o-print.o|[parent_]mm.o|[faulthndlr_]llboot.o;\
mm.o-[parent_]llboot.o|print.o;\
boot.o-print.o|fprr.o|mm.o|llboot.o;\
va.o-fprr.o|print.o|mm.o|l.o|boot.o;\
l.o-fprr.o|mm.o|print.o;\
mpool.o-print.o|fprr.o|mm.o|boot.o|va.o|l.o;\
sm.o-print.o|fprr.o|mm.o|boot.o|va.o|l.o|mpool.o;\
\
pi.o-sm.o|fprr.o|va.o|po.o|print.o|mm.o|va.o;\
po.o-print.o\
" ./gen_client_stub
