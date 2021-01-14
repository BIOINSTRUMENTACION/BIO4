function energy = average_energy(A)
[W,H] = size(A);
sumation =  0;
for w=1:1:W
    for h=1:1:H
        sumation = sumation  +  double(A(w,h));
    end  
end
%energy =  cast(sumation/(W*H),'uint8');
energy =   sumation/(W*H);
end

