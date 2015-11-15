# 1212300229_p1
####周奎君，1212300229，Unix系统分析作业1  分析以下代码中使用的linux系统调用。要求使用strace工具

下面是.c代码：
```
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

//这里用于把输入的内容以空格区分开
int split(char* cmd, char output[5][256]){
    int count = 0; //yongyu jisuan canshu 
    int length = strlen(cmd);
    int i,j=0,flag=0;
    for(i=0; i<length; i++){
        if(cmd[i] == ' '){
            if(count >0 && j!=0){
                output[count-1][j] = '\0';          
            }
            flag = 0;
        }else{
            if(flag == 0){
                count++;
                j = 0;
                flag = 1;           
            }
            output[count -1][j] = cmd[i];
            j++;        
        }
            
    }
    return count;
}
char cmd[256];
char params[5][256];
int counter=0;
void main(){
    int ret;
    printf("Hello World, this is Linux!");
    while(1){
        printf(">");
        fgets(cmd,256,stdin);
        if (cmd[strlen(cmd) - 1] == '\n')
        {  
                    cmd[strlen(cmd) - 1] = '\0';  
                } 
        if(fork() == 0)  
        {    
            counter = split(cmd, params);  
                    if(counter != 0)  
                {   
                    switch(counter)  
                    {  
                        case 0: break;  
                        case 1:   
                        {  
                            execlp(params[0], params[0], NULL);  
                        }      
                        break;  
                        case 2:  
                        {  
                            execlp(params[0], params[0] , params[1], NULL);  
                        }  
                        break;  
                        case 3:  
                        {  
                            printf("%s %s %s\n" ,params[0] ,params[1], params[2]);
                            execlp(params[0], params[0], params[1], params[2],  
                                (char*)0);  
                        }  
                        break;  
                        default:  
                        {  
                            printf("Illegal Input!\n");  
                        }  
                    } // end switch 
                }
                perror(cmd);
                exit(errno);
       }else{  
            wait(&ret);  
            printf("child process return %d\n",ret);  
        }   
    }
        return 0; 
}
```

####gcc编译之后运行之后，运行的程序

```
joe@ubuntu:~/Desktop$ strace -f -F -o ./straceout.txt ./test 
Hello World, this is Linux!>ls -a /home/joe/Desktop
counter = 3
ls -a /home/joe/Desktop
.  ..  1212300229_p1.c  1212300229_p1.c~  straceout.txt  test
child process return 0

```

####以及得到的straceout.txt文件的内容,如下：

```
24261 execve("./test", ["./test"], [/* 65 vars */]) = 0
24261 brk(0)                            = 0xdc4000
24261 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
24261 mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f14dceb9000
24261 access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
24261 open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
24261 fstat(3, {st_mode=S_IFREG|0644, st_size=87094, ...}) = 0
24261 mmap(NULL, 87094, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f14dcea3000
24261 close(3)                          = 0
24261 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
24261 open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
24261 read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\320\37\2\0\0\0\0\0"..., 832) = 832
24261 fstat(3, {st_mode=S_IFREG|0755, st_size=1844160, ...}) = 0
24261 mmap(NULL, 3949184, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f14dc8d4000
24261 mprotect(0x7f14dca8e000, 2097152, PROT_NONE) = 0
24261 mmap(0x7f14dcc8e000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1ba000) = 0x7f14dcc8e000
24261 mmap(0x7f14dcc94000, 17024, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f14dcc94000
24261 close(3)                          = 0
24261 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f14dcea2000
24261 mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f14dcea0000
24261 arch_prctl(ARCH_SET_FS, 0x7f14dcea0740) = 0
24261 mprotect(0x7f14dcc8e000, 16384, PROT_READ) = 0
24261 mprotect(0x600000, 4096, PROT_READ) = 0
24261 mprotect(0x7f14dcebb000, 4096, PROT_READ) = 0
24261 munmap(0x7f14dcea3000, 87094)     = 0
24261 fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 14), ...}) = 0
24261 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f14dceb8000
24261 fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 14), ...}) = 0
24261 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f14dceb7000
24261 write(1, "Hello World, this is Linux!>", 28) = 28
24261 read(0, "ls -a /home/joe/Desktop\n", 1024) = 24
24261 clone(child_stack=0, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7f14dcea0a10) = 26263
24261 wait4(-1,  <unfinished ...>
26263 write(1, "counter = 3\n", 12)     = 12
26263 write(1, "ls -a /home/joe/Desktop\n", 24) = 24
26263 execve("/usr/local/sbin/ls", ["ls", "-a", "/home/joe/Desktop"], [/* 65 vars */]) = -1 ENOENT (No such file or directory)
26263 execve("/usr/local/bin/ls", ["ls", "-a", "/home/joe/Desktop"], [/* 65 vars */]) = -1 ENOENT (No such file or directory)
26263 execve("/usr/sbin/ls", ["ls", "-a", "/home/joe/Desktop"], [/* 65 vars */]) = -1 ENOENT (No such file or directory)
26263 execve("/usr/bin/ls", ["ls", "-a", "/home/joe/Desktop"], [/* 65 vars */]) = -1 ENOENT (No such file or directory)
26263 execve("/sbin/ls", ["ls", "-a", "/home/joe/Desktop"], [/* 65 vars */]) = -1 ENOENT (No such file or directory)
26263 execve("/bin/ls", ["ls", "-a", "/home/joe/Desktop"], [/* 65 vars */]) = 0
26263 brk(0)                            = 0xd2d000
26263 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
26263 mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4656578000
26263 access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
26263 open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
26263 fstat(3, {st_mode=S_IFREG|0644, st_size=87094, ...}) = 0
26263 mmap(NULL, 87094, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f4656562000
26263 close(3)                          = 0
26263 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
26263 open("/lib/x86_64-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
26263 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0000[\0\0\0\0\0\0"..., 832) = 832
26263 fstat(3, {st_mode=S_IFREG|0644, st_size=138384, ...}) = 0
26263 mmap(NULL, 2242448, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f4656134000
26263 mprotect(0x7f4656155000, 2093056, PROT_NONE) = 0
26263 mmap(0x7f4656354000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x20000) = 0x7f4656354000
26263 mmap(0x7f4656356000, 6032, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f4656356000
26263 close(3)                          = 0
26263 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
26263 open("/lib/x86_64-linux-gnu/libacl.so.1", O_RDONLY|O_CLOEXEC) = 3
26263 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0`\34\0\0\0\0\0\0"..., 832) = 832
26263 fstat(3, {st_mode=S_IFREG|0644, st_size=35264, ...}) = 0
26263 mmap(NULL, 2130432, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f4655f2b000
26263 mprotect(0x7f4655f32000, 2097152, PROT_NONE) = 0
26263 mmap(0x7f4656132000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x7000) = 0x7f4656132000
26263 close(3)                          = 0
26263 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
26263 open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
26263 read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\320\37\2\0\0\0\0\0"..., 832) = 832
26263 fstat(3, {st_mode=S_IFREG|0755, st_size=1844160, ...}) = 0
26263 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4656561000
26263 mmap(NULL, 3949184, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f4655b66000
26263 mprotect(0x7f4655d20000, 2097152, PROT_NONE) = 0
26263 mmap(0x7f4655f20000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1ba000) = 0x7f4655f20000
26263 mmap(0x7f4655f26000, 17024, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f4655f26000
26263 close(3)                          = 0
26263 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
26263 open("/lib/x86_64-linux-gnu/libpcre.so.3", O_RDONLY|O_CLOEXEC) = 3
26263 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\26\0\0\0\0\0\0"..., 832) = 832
26263 fstat(3, {st_mode=S_IFREG|0644, st_size=444608, ...}) = 0
26263 mmap(NULL, 2540072, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f46558f9000
26263 mprotect(0x7f4655965000, 2093056, PROT_NONE) = 0
26263 mmap(0x7f4655b64000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6b000) = 0x7f4655b64000
26263 close(3)                          = 0
26263 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
26263 open("/lib/x86_64-linux-gnu/libdl.so.2", O_RDONLY|O_CLOEXEC) = 3
26263 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\320\16\0\0\0\0\0\0"..., 832) = 832
26263 fstat(3, {st_mode=S_IFREG|0644, st_size=14664, ...}) = 0
26263 mmap(NULL, 2109744, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f46556f5000
26263 mprotect(0x7f46556f8000, 2093056, PROT_NONE) = 0
26263 mmap(0x7f46558f7000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7f46558f7000
26263 close(3)                          = 0
26263 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
26263 open("/lib/x86_64-linux-gnu/libattr.so.1", O_RDONLY|O_CLOEXEC) = 3
26263 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\300\20\0\0\0\0\0\0"..., 832) = 832
26263 fstat(3, {st_mode=S_IFREG|0644, st_size=18624, ...}) = 0
26263 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4656560000
26263 mmap(NULL, 2113760, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f46554f0000
26263 mprotect(0x7f46554f4000, 2093056, PROT_NONE) = 0
26263 mmap(0x7f46556f3000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7f46556f3000
26263 close(3)                          = 0
26263 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
26263 open("/lib/x86_64-linux-gnu/libpthread.so.0", O_RDONLY|O_CLOEXEC) = 3
26263 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0 o\0\0\0\0\0\0"..., 832) = 832
26263 fstat(3, {st_mode=S_IFREG|0755, st_size=145224, ...}) = 0
26263 mmap(NULL, 2217232, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f46552d2000
26263 mprotect(0x7f46552ea000, 2097152, PROT_NONE) = 0
26263 mmap(0x7f46554ea000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x18000) = 0x7f46554ea000
26263 mmap(0x7f46554ec000, 13584, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f46554ec000
26263 close(3)                          = 0
26263 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f465655f000
26263 mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f465655d000
26263 arch_prctl(ARCH_SET_FS, 0x7f465655d840) = 0
26263 mprotect(0x7f4655f20000, 16384, PROT_READ) = 0
26263 mprotect(0x7f46554ea000, 4096, PROT_READ) = 0
26263 mprotect(0x7f46556f3000, 4096, PROT_READ) = 0
26263 mprotect(0x7f46558f7000, 4096, PROT_READ) = 0
26263 mprotect(0x7f4655b64000, 4096, PROT_READ) = 0
26263 mprotect(0x7f4656132000, 4096, PROT_READ) = 0
26263 mprotect(0x7f4656354000, 4096, PROT_READ) = 0
26263 mprotect(0x61b000, 4096, PROT_READ) = 0
26263 mprotect(0x7f465657a000, 4096, PROT_READ) = 0
26263 munmap(0x7f4656562000, 87094)     = 0
26263 set_tid_address(0x7f465655db10)   = 26263
26263 set_robust_list(0x7f465655db20, 24) = 0
26263 rt_sigaction(SIGRTMIN, {0x7f46552d8a10, [], SA_RESTORER|SA_SIGINFO, 0x7f46552e1c90}, NULL, 8) = 0
26263 rt_sigaction(SIGRT_1, {0x7f46552d8aa0, [], SA_RESTORER|SA_RESTART|SA_SIGINFO, 0x7f46552e1c90}, NULL, 8) = 0
26263 rt_sigprocmask(SIG_UNBLOCK, [RTMIN RT_1], NULL, 8) = 0
26263 getrlimit(RLIMIT_STACK, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
26263 statfs("/sys/fs/selinux", 0x7fffad3ca9e0) = -1 ENOENT (No such file or directory)
26263 statfs("/selinux", 0x7fffad3ca9e0) = -1 ENOENT (No such file or directory)
26263 brk(0)                            = 0xd2d000
26263 brk(0xd4e000)                     = 0xd4e000
26263 open("/proc/filesystems", O_RDONLY) = 3
26263 fstat(3, {st_mode=S_IFREG|0444, st_size=0, ...}) = 0
26263 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4656577000
26263 read(3, "nodev\tsysfs\nnodev\trootfs\nnodev\tr"..., 1024) = 310
26263 read(3, "", 1024)                 = 0
26263 close(3)                          = 0
26263 munmap(0x7f4656577000, 4096)      = 0
26263 open("/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
26263 fstat(3, {st_mode=S_IFREG|0644, st_size=4640112, ...}) = 0
26263 mmap(NULL, 4640112, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f4654e65000
26263 close(3)                          = 0
26263 ioctl(1, SNDCTL_TMR_TIMEBASE or SNDRV_TIMER_IOCTL_NEXT_DEVICE or TCGETS, {B38400 opost isig icanon echo ...}) = 0
26263 ioctl(1, TIOCGWINSZ, {ws_row=24, ws_col=80, ws_xpixel=0, ws_ypixel=0}) = 0
26263 stat("/home/joe/Desktop", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
26263 openat(AT_FDCWD, "/home/joe/Desktop", O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC) = 3
26263 getdents(3, /* 6 entries */, 32768) = 192
26263 getdents(3, /* 0 entries */, 32768) = 0
26263 close(3)                          = 0
26263 fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 14), ...}) = 0
26263 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4656577000
26263 write(1, ".  ..  1212300229_p1.c\t121230022"..., 61) = 61
26263 close(1)                          = 0
26263 munmap(0x7f4656577000, 4096)      = 0
26263 close(2)                          = 0
26263 exit_group(0)                     = ?
26263 +++ exited with 0 +++
24261 <... wait4 resumed> [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 26263
24261 --- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=26263, si_status=0, si_utime=0, si_stime=0} ---
24261 write(1, "child process return 0\n", 23) = 23
24261 write(1, ">", 1)                  = 1
24261 read(0, 0x7f14dceb7000, 1024)     = ? ERESTARTSYS (To be restarted if SA_RESTART is set)
24261 --- SIGINT {si_signo=SIGINT, si_code=SI_KERNEL} ---
24261 +++ killed by SIGINT +++
```
