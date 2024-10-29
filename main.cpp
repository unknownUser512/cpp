#include "func_2.h"
#include <iostream>

int main()
{
    constexpr int size = 4;
    int *ip = new int[size];
    int *mask = new int[size];
    int *net_add = new int[size]; 
    int *mask_neg = new int[size]; 
    int *broad_add = new int[size];
    int short_mask = 0;
   
    std::cout << "Hello. Please enter an IP ADDRESS separated by a space: ";
    ///////////_________#1_WPROWADZANIE_IP_________///////////
    for(int i=0; i<4;)
        {
            static bool wrong = false;
            while(i<4)
            {  
             std::cin >> *(ip+i); 

                if(*(ip+i) >=0 && *(ip+i) <=255)
                {
                    ++i;
                }
                else
                {   
                    *(ip+i) = 0; ++i; wrong = true;
                }
            }
            if(wrong)
            {
                std::cout << "Incorrect ip address. Please try again.\n";
                i=0; wrong = false;
            }
        }   
  

   std::cout << "Next enter the network mask (separated by a space): ";
    ///////////_________#2_WPROWADZANIE_MASKI_________///////////

for(int i=0; i<4;)
{   
    static bool wrong = false;
    static constexpr int correctly[8] = {0, 128, 192, 224, 240, 248, 252, 255};
    static int control =0;
    static int loop_counter =0;
    while(i<4)
    {
    if(i == 0)
    { 
    std::cin >> *(mask+i); 
    if(*(mask+i) >=128 && *(mask+i) <=255)
    {
        for(int j=1; j<=7; ++j)
        {  
             if(*(mask+i) == correctly[j])
        {
        provide_mask(mask, mask_neg, ip, net_add, broad_add, short_mask, control);
            ++i;
            break;
        }
        }
        if(i==0)
        {
            *(mask+i)= -1; ++i; ++control; wrong = true; 
        }
    }
    else
    {  
         *(mask+i) = -1; ++i; ++control; wrong = true;
    }
    }
    /////////////////////////////////////////////////
    if(i==1 || i==2)
    {
    std::cin >> *(mask+i);
    if(*(mask+(i-1))!=-1 && *(mask+i) >=0 && *(mask+i) <=255)
    {
     if(*(mask+(i-1))==255)
           {
           for(int j=0; j<=7; ++j)
        {
            if(*(mask+i)==correctly[j])
            {
            provide_mask(mask, mask_neg, ip, net_add, broad_add, short_mask, control);
            ++i; loop_counter =0;
            break;
            }
            ++loop_counter;
        }
              if(loop_counter==8)
              {
                 *(mask+i) = -1; ++i; ++control; wrong = true; loop_counter = 0;
              }
           }
        else if(*(mask+(i-1)) < 255)
        {
            if(*(mask+i) != 0)
            {
                *(mask+i)= -1; ++i; ++control; wrong = true;
            }
            else
            { 
              provide_mask(mask, mask_neg, ip, net_add, broad_add, short_mask, control);
                ++i;
            }
        } 
    }
    else
    {
        *(mask+i) = -1; ++i; ++control; wrong = true; 
    }
    }
///////////////////////////////////////////////////////////
    if(i==3)
   { 
    std::cin >> *(mask+i);

     if(*(mask+(i-1))!=-1 && *(mask+i) >=0 && *(mask+i)<=252)
 {
     if(*(mask+(i-1))==255)
           {
        for(int j=6; j>=0; --j)
        {
            if(*(mask+i)==correctly[j])
            {
            provide_mask(mask, mask_neg, ip, net_add, broad_add, short_mask, control);
            ++i; loop_counter =0;
            break;
            }
            ++loop_counter;
        }
            
            if(loop_counter==7)
            {
                 *(mask+i) = -1; ++i; ++control; wrong = true; loop_counter = 0;
            }
           }

        else if(*(mask+(i-1)) < 255)
        {
            if(*(mask+i) !=0)
            {   
              *(mask+i) = -1; ++i; ++control; wrong = true;
            }
            else
            {   provide_mask(mask, mask_neg, ip, net_add, broad_add, short_mask, control);
                ++i; 
            }
        } 
   }
   else
   {
     *(mask+i) = -1; ++i; ++control;  wrong = true;
   }
    }
    }
          if(wrong)
        {
            std::cout << "Incorrect mask. Please try again.\n";
            control = 0; short_mask =0;
            i=0; wrong = false;
        }
}
   display_net_br(net_add, broad_add, short_mask);

 ///////////_________#3_PODZIAŁ SIECI_________///////////

if(short_mask<=29)
{
std::cout << "==========================================================================";
int user_Response;
std::cout << "\nHow many networks do you want in total?\n"; 
display_correct_quantity(short_mask);
do
{
std::cout << "Your choice: ";
std::cin >> user_Response;
std::cout << "\n";
if(compare_shortMask(short_mask, user_Response))
{
    change_mask(mask, short_mask);
    network_division(mask, mask_neg, net_add, broad_add, user_Response, short_mask);
    break;
}
else
{
    std::cout << "Wrong quantity. Please try again.\n";
}
}while(true);
}

delete [] ip; delete [] mask; delete [] net_add; delete [] broad_add;delete [] mask_neg;

    return 0;
}
