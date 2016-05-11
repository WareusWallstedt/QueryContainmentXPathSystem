format long
A = [
	0	0.360000	9624.350000	9630.760000;
	1	15849.780000	15274.530000	15132.680000;
	2	40713.590000	36966.180000	36693.190000;
	3	116713.110000	111611.600000	111477.460000;
	4	150235.570000	141116.920000	141238.860000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantGraph.png');
