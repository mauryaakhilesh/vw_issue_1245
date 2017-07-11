# vw_issue_1245
Repo to replicate memory leak issue in vowpal wabbit

What i have did :
	1. I have compiles vowpal_wabbit with static (`make CXX='clang++ -static'`) and copied in lib directory (`$(LIB_DIR)/vw/libvw.a $(LIB_DIR)/vw/liballreduce.a`).

Steps to run :
 1. clone the repo and execute `run.sh` (after installing all the dependencies)

I have used `Red Hat Enterprise Linux Server release 6.2 (Santiago) 64 bit architecture `  system to replicate issue and libboot 1.59