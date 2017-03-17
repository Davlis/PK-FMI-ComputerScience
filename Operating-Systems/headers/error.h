void error(const char* error){
	perror(error);
	exit(errno);
}