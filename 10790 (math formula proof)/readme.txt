10790 - How Many Points of Intersection?
https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=99&page=show_problem&problem=1731

The statement shows an image of a complete bipartite graph. The task is to calculate the maximum number of the internal intersections.

The basic approach for understanding the solution can be generating the pairs of intersecting segments.

There is A top points and B bottom points.
Each intersection is decoded as [(i0, j0)(i1, j1)].
Let us assume that the segments are intersecting in two cases:
1) i0 < i1 && j0 > j1;
2) i0 > i1 && j0 < j1.

So we iterate making unique intersections:
for i0 in range [1, A]/*cycle through all A points*/
	for j0 in range [1, B]/*cycle through all B points*/
		for i1 in range [i0 + 1, A]/*cycle through points on the right of the side A*/
			for j1 in range [1, j0 - 1]/*cycle through points on the left of the side B*/

Cycle by i1 has (A-1)+(A-2)+...+1 iterations.
Cycle by j1 has 1+2+3+...+(B-1) iterations.

So the result is the multiplication of two arithmetic progressions (A(A-1)/2)*(B(B-1)/2), and the above is the proof why it works.