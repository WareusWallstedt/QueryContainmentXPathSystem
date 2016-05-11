format long
A = [
	0	1.957400	0.946600;
	1	2.770000	2.215700;
	2	5.072100	4.080200;
	3	9.914800	7.671100;
	4	20.219200	15.099600;
	5	41.414800	31.357600;
	6	85.019700	53.872700;
	7	173.852200	110.148500;
	8	353.555900	217.391100;
	9	714.119000	461.565000;
	10	1424.053200	1006.507700;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildBranchRank2WildcardGraph.png');
