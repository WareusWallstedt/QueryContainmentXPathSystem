format long
A = [
	0	0.390000	9592.080000	9605.360000;
	1	16057.430000	15586.500000	15194.170000;
	2	37659.270000	35514.350000	35429.030000;
	3	114359.660000	110876.610000	111300.370000;
	4	146922.850000	139522.800000	139611.890000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantGraph.png');
