__kernel
void Multiply(
 __global float*       A,
 __global float*       B,
 __global float*       Output,
 const    unsigned int N
){
 const int i = get_global_id(1); // Row
 const int j = get_global_id(0); // Column

 int k;
 float result = 0;
 for(k = 0; k < N; k++){
  result += A[N*i + k] * B[N*k + j];
 }
 Output[N*j + i] = result;
}
//------------------------------------------------------------------------------

