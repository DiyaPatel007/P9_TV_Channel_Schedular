# P9_TV_Channel_Schedular
Capstone
You are to build a TV Channel Scheduler. The Scheduler works for family
members who want to record their favorite TV series so that they can watch
them later and get notified by the Scheduler when they have time (it knows their
availability slots - randomly initialized). There are N members in a family, each
having their favorite series out of a total of M. Multiple members may love the
same series. However, the Scheduler cannot schedule a series if there is a
conflict of interest. Also, members want to get on time for p slots. The Scheduler
needs to minimize total episode misses.

# Comments:
● Input data will be a file (can be txt or xls) with records in the format<br>
○ Family member name<br>
○ Availability slots (will be a set of time intervals for each of 7 days)<br>
○ Set (S) of favorite TV series (S <= M)<br>
● Conflict of interest means two or more overlapping intervals<br>
● “Also, members want to get on time for p slots”: This means for at least p slots (out of S), every member wants to be on time and not wait.<br>

Description of our project
In this code we are taking a csv file of the family members as the input to our code. The input file contains necessary details of the family member name,its free time,its show time and also the show name liked by the family member.
As output,we are going to display the recorded shows of the user,also user is able to watch the recorded show on its free time.
The main feature of our code is that it is able to handle the conflict of the user having same shows as well as the the user having different shows at the same time.
With this our code could successfully able to schedule time for the family members thus giving the desired output to them. 

