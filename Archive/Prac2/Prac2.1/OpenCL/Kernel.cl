__kernel void HelloWorld(__global int* argument1, __global int* argument2, __global int* output){
	//work item and work groups numbers
	int workItemNum = get_global_id(0); //Work item ID
	int workGroupNum = get_group_id(0); //Work group ID
	int localGroupID = get_local_id(0); //Work items ID within each work group
	
	//memory buffers
	int arg1 = *argument1;
	int arg2 = *argument2;
	uint global_addr = workItemNum;
	
	//short calculation: work Item Number x argument 1 + argument 2
	//TODO: perform the required calculation
	printf("Hello World\n");

	//TODO: print the work item, work group and arguments
	/*
	Expected Output:
	Hi from work item: 0 	 work group:0 	 Arg1: 10 	 Arg2: 20 	 Output: 20 
	Hi from work item: 1 	 work group:0 	 Arg1: 10 	 Arg2: 20 	 Output: 30 
	Hi from work item: 2 	 work group:0 	 Arg1: 10 	 Arg2: 20 	 Output: 40 
	Hi from work item: 3 	 work group:0 	 Arg1: 10 	 Arg2: 20 	 Output: 50 
	Hi from work item: 8 	 work group:2 	 Arg1: 10 	 Arg2: 20 	 Output: 100 
	Hi from work item: 9 	 work group:2 	 Arg1: 10 	 Arg2: 20 	 Output: 110 
	Hi from work item: 10 	 work group:2 	 Arg1: 10 	 Arg2: 20 	 Output: 120 
	Hi from work item: 11 	 work group:2 	 Arg1: 10 	 Arg2: 20 	 Output: 130 
	Hi from work item: 4 	 work group:1 	 Arg1: 10 	 Arg2: 20 	 Output: 60 
	Hi from work item: 5 	 work group:1 	 Arg1: 10 	 Arg2: 20 	 Output: 70 
	Hi from work item: 6 	 work group:1 	 Arg1: 10 	 Arg2: 20 	 Output: 80 
	Hi from work item: 7 	 work group:1 	 Arg1: 10 	 Arg2: 20 	 Output: 90 
	Hi from work item: 12 	 work group:3 	 Arg1: 10 	 Arg2: 20 	 Output: 140 
	Hi from work item: 13 	 work group:3 	 Arg1: 10 	 Arg2: 20 	 Output: 150 
	Hi from work item: 14 	 work group:3 	 Arg1: 10 	 Arg2: 20 	 Output: 160 
	Hi from work item: 15 	 work group:3 	 Arg1: 10 	 Arg2: 20 	 Output: 170 
	*/

	
	//barrier that stops all work items here until all work items in the work group have executed this function
	barrier(CLK_LOCAL_MEM_FENCE);
	
	//adding the outputs for each group---------------------------------------------
	int groupValue = 0;
	//TODO: Add all the work items in each work group and output the work groups total 
	//Expected output:
	//groupValue: 300 	 Work item:4 	 Work group: 1 
	//groupValue: 620 	 Work item:12 	 Work group: 3 
	//groupValue: 140 	 Work item:0 	 Work group: 0 
	//groupValue: 460 	 Work item:8 	 Work group: 2 
	//--------------------------------------------------------------------------------
	
	
}


