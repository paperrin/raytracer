void	atomic_addf(volatile global float *source, const float operand);

void	atomic_addf(volatile global float *source, const float operand)
{
	union {
		unsigned int	int_val;
		float			float_val;
	}	u_new_val;
	union {
		unsigned int	int_val;
		float			float_val;
	}	u_prev_val;

	do {
		u_prev_val.float_val = *source;
		u_new_val.float_val = u_prev_val.float_val + operand;
	} while (atomic_cmpxchg((volatile global unsigned int *)source, u_prev_val.int_val, u_new_val.int_val) != u_prev_val.int_val);
}
