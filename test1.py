#!/usr/bin/env python
# coding: utf-8

# In[23]:


d = {}          #dictionary for data importing
dicts=[]        #list for storing all dictionaries
my_dict={}      #dictionary for filtered data

                #extracting data
    
with open("test1.txt") as f:
    for line in f:
        (key, val) = line.strip().split(' ',1)   #splitting the lines 
        d[str(key)] = val                        #mapping
    print('given data is:',d)
    
keys=list((d.keys()))           # getting keys
values1=list((d.values()))      # getting values

print('\n')

values2=str(values1)
j=0

                 #creation of new skeleton for new dictionanary 
for i in range(len(keys)):
    
    my_dict[keys[i]]=''


values_roll=values1[0]       #slicing and associating values per key 
values_pitch=values1[1]
values_yaw=values1[2]


values_roll1=values_roll.split(',')     #splitting values


values_pitch1=values_pitch.split(',')


values_yaw1=values_yaw.split(',')


all_vals=values_roll1+values_pitch1+values_yaw1     # total number of values

               #generation of final dictionary with appending it to a list 

for my_dict1 in range(int(len(all_vals)/len(keys))):
        
    my_dict11={keys[0]: values_roll1[my_dict1],keys[1]:values_pitch1[my_dict1],keys[2]:values_yaw1[my_dict1]}
    
    print('generated dictionary',my_dict1,'\n',my_dict11)
    print('\n')
    dicts.append(my_dict11)

print('generated list of dictionaries\n',dicts)

