format long
A = [
	0	1.869000	0.979100;
	1	2.681700	2.224000;
	2	5.138100	4.111200;
	3	8.344100	6.627100;
	4	13.172000	9.807400;
	5	18.519400	14.007100;
	6	26.306700	18.893200;
	7	34.352500	25.505200;
	8	42.653800	28.270300;
	9	54.873500	34.447600;
	10	64.865800	42.201600;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildBranchDepth2WildcardGraph.png');
