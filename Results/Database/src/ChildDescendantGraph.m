format long
A = [
	0	0.360000	9556.010000	9535.410000;
	1	15907.600000	15420.400000	15220.160000;
	2	37862.960000	35636.210000	35888.670000;
	3	114833.780000	110329.500000	110343.530000;
	4	146724.730000	140919.320000	139809.360000;
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
