The problem has been solved with three different strategies (yet), none of which, however, guarantee the lowest possible number of antennas.

The first chooses a random initial position of antennas and places the next ones in the neighbourhood of the previous ones, in order to maximise the number of blocks covered.

The second always takes the block on the island with the lowest coverage density (when an antenna is supposed to be on it) and chooses an antenna location such as the block that, within the radius, contains it but maximises its coverage.

The third uses the same idea as the second, but in the neighbourhood of the previous point.

The second strategy is the one that, of the three, guarantees the fewest antennas overall, followed by the third and finally the first.

The points were plotted on graphs and, for each strategy, the antennas were positioned and their coverage radii were plotted. They are shown below.

Strategy 1:
![Plot_opt_1](https://github.com/user-attachments/assets/44a38ef2-5153-4486-9473-0b68528458ab)

Strategy 2:
![Plot_opt_2](https://github.com/user-attachments/assets/7f2340d3-c533-46ac-accb-d8e8eb5daeda)

Strategy 3:
![Plot_opt_3](https://github.com/user-attachments/assets/757dc59c-710f-41b2-8403-10e58c25f819)

