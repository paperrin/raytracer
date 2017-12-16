	__kernel void add42(__global float *in, __global float *out)
	{
   		unsigned int i = get_global_id(0);
		out[i] = in[i] + 42;
	}
