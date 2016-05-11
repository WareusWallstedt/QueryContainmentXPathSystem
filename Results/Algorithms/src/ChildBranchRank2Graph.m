format long
A = [
	0	1.899600	0.940300;
	1	2.762800	2.249400;
	2	5.339900	4.272800;
	3	10.323200	8.008800;
	4	20.625300	16.263400;
	5	42.898700	31.904100;
	6	87.561200	57.730400;
	7	179.689700	119.232000;
	8	359.360100	236.158000;
	9	718.797100	466.005000;
	10	1488.292800	1081.569500;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildBranchRank2Graph.png');
