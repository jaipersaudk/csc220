clc;
clear all;
close all;

cities = 10;  %number of cities
Pop = 100; %size of Population (# of paths - only 100 out of 10!)
G = 25;  %how many Generations


% random dimensions for the cities in a unit square
points = rand(cities,2)*1;

%creates scatter plot of random points
scatter(points(:,1),points(:,2),'MarkerEdgeColor','r','MarkerFaceColor','y')

%computing distance between each city
for i = 1:cities
    for j=1:cities
        Dist(i,j)=sqrt((points(i,1)-points(j,1))^2 +(points(i,2)-points(j,2))^2); %compute distance betweeen points
    end
end

% 100 random paths are generated (population is randomized)
for i=1:Pop
    R(i,:)=randperm(cities);
end

%for each generation
for generations=1:G
    
%computing the fitness for each population by computing their distances
for i=1:Pop
    
    sum1=Dist(R(i,1),R(i,10));
    sum2=0;
    for j=1:cities-1
    sum2=Dist(R(i,j),R(i,j+1))+sum2;
    end
    R(i,11)=sum1+sum2;
end
R=sortrows(R,11); %sort matrix according to their fitness value


% cross over probabilty of 80 and mutation probability of 10
c=randperm(80);
mut=randperm(10);

%cross over function to increase population size by 80 (2 children per loop for 40 loops)
for i=1:40
    %creating zero matrices for both children
    c1=zeros(1,10);
    c2=zeros(1,10);

    %tournament selection - choosing the best parents from the population to make children
    %choosing parents from the existing population and computing values for the children 
    p1=R(c(2*i),1:10);
    p2=R(c(2*i-1),1:10);
    
    %creating new children
    c1(1,mut(1:3))=p1(1,mut(1:3));
    c2(1,mut(1:3))=p2(1,mut(1:3));
   

[y1,x1]=find(c1==0);   
d=0;
e=1;
   for j=1:cities
       for k=1:cities
   if c1(k)==p2(j) 
       d=1;
   end
       end
       if d~=1
           c1(x1(e))=p2(j);
           e=e+1;
       else
           d=0;
       end
   end
d=0;
e=1;
   for j=1:cities
       for k=1:cities
   if c2(k)==p1(j)
       d=1;
   end
       end
       if d~=1
           c2(x1(e))=p1(j);
           e=e+1;
       else
           d=0;
       end
   end
   R(100+2*i-1,1:10)=c1;
   R(100+2*i,1:10)=c2;
       
end

%finding fitness value for the new population of size 180 (100 from initial + 80 from children)
for i=1:Pop+0.8*Pop
    sum1=Dist(R(i,1),R(i,10));
    sum2=0;
    for j=1:cities-1
    sum2=Dist(R(i,j),R(i,j+1))+sum2;
    end
    R(i,11)=sum1+sum2;
end
R=sortrows(R,11); %%sort the matrix according to their fitness value

%select the best 100 from the total 180 population (shortest paths)
R=R(1:100,:);
c=R;
c(:,11)=R(:,1);

%drawing the shortest paths on the graph
min_path=min(R(:,11)); %used to display the shortest path
plot(points(c(1,1:11),1),points(c(1,1:11),2),points(c(1,1:11),1),points(c(1,1:11),2),'o','MarkerEdgeColor','b','MarkerFaceColor','y','MarkerSize',7)
text(max(points(:,1))+2,max(points(:,2))+2,num2str(min_path),'HorizontalAlignment','center')
pause(1)
end