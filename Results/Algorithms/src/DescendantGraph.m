format long
A = [
	0	1.865400	0.944000;
	1	3.026800	1.827700;
	2	4.814700	1.616400;
	3	7.913400	1.987700;
	4	15.019100	2.332200;
	5	30.926400	2.767700;
	6	66.181300	2.939100;
	7	144.772900	3.212700;
	8	315.437600	3.593300;
	9	696.208700	4.102000;
	10	1563.457700	4.516000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantGraph.png');
