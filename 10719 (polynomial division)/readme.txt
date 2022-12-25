10719 - Quotient Polynomial
https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1660

The task is to solve coefficients of p(x)=(x-k)q(x)+r where p(x) and k are provided.

Let's assume this is p(x):
a[n]x^n + a[n-1]x^(n-1) + ... + a[1]x + a0

p(x) is divided by (x-k) from (a[n],a[n-1]) to (a1,a0) using iterative approach:

	divide (a[i], a[i-1], k)
		a[i-1]' = a[i]
		r = a[i-1] - (a[i]*-k)
		return {a[i-1]', r}

This is the basic approach for the calculation.