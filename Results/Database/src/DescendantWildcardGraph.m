format long
A = [
	0	0.360000	9533.570000	9483.720000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantWildcardGraph.png');
