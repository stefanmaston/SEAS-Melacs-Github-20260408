#ifndef __SSH_H__
#define __SSH_H__

typedef struct {
	int (*posh_start)(void *);
	int (*sftp_start)(void *);
} tshell_init;

void sshd(char *config_path, tshell_init * shell);

#endif //__SSH_H__
