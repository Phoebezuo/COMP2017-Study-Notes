#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {

	if(argc > 1) {
	//quick and dirty method of parsing the arguments
		char* cmd_ptr = (strstr(argv[1], "=")+1);
		
		char buf[1024];
		FILE* output_file = stdout;
		FILE* f = popen(cmd_ptr, "r");
		if (argc > 2){
			char* out_ptr = (strstr(argv[2], "=")+1); 
			output_file = fopen(out_ptr, "w"); 
		}
		printf(":::Process Logger Started:::");
		//Reading the output of the process running
		size_t bytes = 0;
		while ((bytes = fread(buf, sizeof(char), 1024, f)) > 0) {
			fwrite(buf, sizeof(char), bytes, output_file);
		}
		if (argc > 2){
			fclose(output_file);
		}
		printf(":::Process Logger Ended:::\n");
		pclose(f);
	}

}
