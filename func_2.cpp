#include "..\headers\func_2.h"
#include <bitset>
#include <iostream>
#include <math.h>

void provide_mask(int*mask, int*mask_neg, int*ip, int*net_add, 
int*broad_add, int&short_mask, int&control)
{ 
    std::bitset<8> number_ofb(*(mask+control));
    short_mask += number_ofb.count();
    *(net_add+control) = *(mask+control) & *(ip+control);
    *(mask_neg+control) = *(mask+control) ^ 0xFF;
    *(broad_add+control) = *(net_add+control) + *(mask_neg+control);
    ++control;  
}

//////////////////////////////////////////////////////////

void display_net_br(const int* net_add, const int*broad_add, const int& short_mask)
{
    std::cout << "NETWORK ADDRESS: " << *net_add << "." << *(net_add+1) << "." <<
         *(net_add+2) << "." << *(net_add+3) << " - ";

std::cout << "BROADCAST ADDRESS: " << *broad_add << "." << *(broad_add+1) << "." << 
      *(broad_add+2) << "." << *(broad_add+3) << "/" << short_mask << "\n";

 std::cout << "Available host addresses: " << *net_add << "." << *(net_add+1)
<< "." << *(net_add+2) << "." << *(net_add+3) +1 << " - " << *broad_add << "." 
<< *(broad_add+1) << "." << *(broad_add+2)  << "." << *(broad_add+3)-1 << "\n";

int sum = std::pow(2, (32-short_mask)) - 2;
 std::cout << "Maxiumum number of active hosts: " << sum << "\n\n";
 
}

//////////////////////////////////////////////////////////

void display_correct_quantity(const int& short_mask)
{
    if (short_mask<=26)
    {
        std::cout << "Correct quantities: 2, 4, 8, 16\n";
    }
    else if (short_mask<=27)
    {
        std::cout << "Correct quantities: 2, 4, 8\n";
    }
     else if (short_mask<=28)
    {
        std::cout << "Correct quantities: 2, 4\n";
    }
    else if(short_mask<=29)
    {
        std::cout << "Correct quantity: 2\n";
    }
}

//////////////////////////////////////////////////////////

const bool compare_shortMask(int& curent_shortMask, const int& user_Response)
{
    if(user_Response==2)
    {
        if(curent_shortMask <= 29)
        {   
            ++curent_shortMask;
            return true;
        }
        else
        {  
            return false;
        }
    }
    
    //
    else if(user_Response == 4)
    {
        if(curent_shortMask <= 28)
        {
            curent_shortMask += 2;
            return true;
        }
        else
        {
            return false;
        }
    }
    //
    else if(user_Response == 8)
    {
        if(curent_shortMask <= 27)
        {
            curent_shortMask += 3;
            return true;
        }
        else
        {
            return false;
        }
    }
  else if(user_Response == 16)
    {
        if(curent_shortMask <= 26)
        {
            curent_shortMask += 4;
            return true;
        }
        else
        {
            return false;
        }
    }
   else
   {
     return false;
   }

}

//////////////////////////////////////////////////////////

void change_mask(int* mask, const int& short_mask)
{
    switch(short_mask)
    {
        case 2: *mask = 192; break;
        case 3: *mask = 224; break;
        case 4: *mask = 240; break;
        case 5: *mask = 248; break;
        case 6: *mask = 252; break;
        case 7: *mask = 254; break;
        case 8: *mask = 255; break;
        ////
        case 9: *(mask+1) = 128; break;
        case 10: *(mask+1) = 192; break;
        case 11: *(mask+1) = 224; break;
        case 12: *(mask+1) = 240; break;
        case 13: *(mask+1) = 248; break;
        case 14: *(mask+1) = 252; break;
        case 15: *(mask+1) = 254; break;
        case 16: *(mask+1) = 255; break;
        ////
        case 17: *(mask+2) = 128; break;
        case 18: *(mask+2) = 192; break;
        case 19: *(mask+2) = 224; break;
        case 20: *(mask+2) = 240; break;
        case 21: *(mask+2) = 248; break;
        case 22: *(mask+2) = 252; break;
        case 23: *(mask+2) = 254; break;
        case 24: *(mask+2) = 255; break;
        ////
        case 25: *(mask+3) = 128; break;
        case 26: *(mask+3) = 192; break;
        case 27: *(mask+3) = 224; break;
        case 28: *(mask+3) = 240; break;
        case 29: *(mask+3) = 248; break;
        case 30: *(mask+3) = 252; break;
    }
}

////////////////////////////////////////////////////

void network_division(int*mask, int*mask_neg, int*net_add, int*broad_add, 
const int& userChoice,  int& short_mask)
{
    char choice;

restart_maskAndBroad(mask, mask_neg, net_add, broad_add);

int quantity =0, counter = 1;
if(userChoice==2) {quantity = 1;}
else if(userChoice==4) {quantity = 2;}
else if(userChoice==8) {quantity = 4;}
else if(userChoice==16) {quantity = 8;}

    if(short_mask >= 25 && short_mask <= 30)
    {
        for(int i=0; i<quantity; ++i)
        {
            if(i > 0)
            {
                *(broad_add+3) +=1;
                new_network(net_add, broad_add, mask_neg);
            }
 std::cout << "Network " << counter << ": "; ++counter;

       display_net_br(net_add, broad_add, short_mask);

        *(broad_add+3) +=1;
     new_network(net_add, broad_add, mask_neg);


       std::cout << "Network " << counter << ": "; ++counter;
   display_net_br(net_add, broad_add, short_mask);
        }


        if(short_mask <=29)
        {
        char choice;
        std::cout << "Would you like to add another subnet? 1.Yes 2.No\nYour choice: ";
        std::cin >> choice; std::cout << "\n";
         if(choice == '1')
        {   
            --counter;
           add_another(mask, mask_neg, net_add, broad_add, short_mask, counter);

               *(broad_add+3) +=1;
     new_network(net_add, broad_add, mask_neg);

    ++counter;
       std::cout << "Network " << counter << ": "; ++counter;
   display_net_br(net_add, broad_add, short_mask);
        }
        else 
        {
            exit(0);
        }
        }      
    }

//////////////////////////////////////////////////////////////////////////////

    else if(short_mask >= 17 && short_mask <= 24)
    {

         for(int i=0; i<quantity; ++i)
        {
            if(i > 0)
            {
                *(broad_add+3) = 0; *(broad_add+2) +=1;
                new_network(net_add, broad_add, mask_neg);
            }
 std::cout << "Network " << counter << ": "; ++counter;

       display_net_br(net_add, broad_add, short_mask);

        *(broad_add+3) = 0; *(broad_add+2) +=1;
     new_network(net_add, broad_add, mask_neg);


       std::cout << "Network " << counter << ": "; ++counter;
   display_net_br(net_add, broad_add, short_mask);
        }
        if(short_mask <=29)
        {
        char choice;
          std::cout << "Would you like to add another subnet? 1.Yes 2.No\nYour choice: ";
        std::cin >> choice; std::cout << "\n";
         if(choice == '1')
        {   
            --counter;
           add_another(mask, mask_neg, net_add, broad_add, short_mask, counter);

              
        *(broad_add+3) = 0; *(broad_add+2) +=1;
     new_network(net_add, broad_add, mask_neg);

    ++counter;
       std::cout << "Network " << counter << ": "; ++counter;
   display_net_br(net_add, broad_add, short_mask);
        }
         else 
        {
            exit(0);
        }
        }      
    }

//////////////////////////////////////////////////////////////////////////////

    else if(short_mask >=9 && short_mask <=16)
    {

 for(int i=0; i<quantity; ++i)
        {
            if(i > 0)
            {
                  *(broad_add+3) = 0; *(broad_add+2) = 0; *(broad_add+1) +=1;
                new_network(net_add, broad_add, mask_neg);
            }
 std::cout << "Network " << counter << ": "; ++counter;

       display_net_br(net_add, broad_add, short_mask);

          *(broad_add+3) = 0; *(broad_add+2) = 0; *(broad_add+1) +=1;
     new_network(net_add, broad_add, mask_neg);


       std::cout << "Network " << counter << ": "; ++counter;
   display_net_br(net_add, broad_add, short_mask);
        }


        if(short_mask <=29)
        {
        char choice;
    std::cout << "Would you like to add another subnet? 1.Yes 2.No\nYour choice: ";
        std::cin >> choice; std::cout << "\n";
         if(choice == '1')
        {   
            --counter;
           add_another(mask, mask_neg, net_add, broad_add, short_mask, counter);

                *(broad_add+3) = 0; *(broad_add+2) = 0; *(broad_add+1) +=1;
     new_network(net_add, broad_add, mask_neg);

    ++counter;
       std::cout << "Network " << counter << ": "; ++counter;
   display_net_br(net_add, broad_add, short_mask);
        }
         else 
        {
            exit(0);
        }
        }    
    }
   
//////////////////////////////////////////////////////////////////////////////

        else if(short_mask >=1 && short_mask <=8)
        {

             for(int i=0; i<quantity; ++i)
        {
            if(i > 0)
            {
                 *(broad_add+3) = 0; *(broad_add+2) = 0; *(broad_add+1) =0; *(broad_add) +=1;
                new_network(net_add, broad_add, mask_neg);
            }
 std::cout << "Network " << counter << ": "; ++counter;

       display_net_br(net_add, broad_add, short_mask);

         *(broad_add+3) = 0; *(broad_add+2) = 0; *(broad_add+1) =0; *(broad_add) +=1;
     new_network(net_add, broad_add, mask_neg);


       std::cout << "Network " << counter << ": "; ++counter;
   display_net_br(net_add, broad_add, short_mask);
        }


        if(short_mask <=29)
        {
        char choice;
        std::cout << "Would you like to add another subnet? 1.Yes 2.No\nYour choice: ";
        std::cin >> choice; std::cout << "\n";
         if(choice == '1')
        {   
            --counter;
           add_another(mask, mask_neg, net_add, broad_add, short_mask, counter);

             *(broad_add+3) = 0; *(broad_add+2) = 0; *(broad_add+1) =0; *(broad_add) +=1;
     new_network(net_add, broad_add, mask_neg);

    ++counter;
       std::cout << "Network " << counter << ": "; ++counter;
   display_net_br(net_add, broad_add, short_mask);
        }
         else 
        {
            exit(0);
        }
        }   
        }  
}

////////////////////////////////////////////////////

void restart_maskAndBroad(int*mask, int*mask_neg, int*net_add, int*broad_add)
{
     for(int i=0; i<4; ++i)
    {
        *(broad_add+i) = *(net_add+i);
        *(mask_neg+i) = *(mask+i) ^ 0xff;
        *(broad_add+i) += *(mask_neg+i);
    }
}

////////////////////////////////////////////////////

void new_network(int*net_add, int*broad_add, int* mask_neg)
{ 
 for(int i=0; i<4; ++i)
 
    { 
            *(net_add+i) = *(broad_add+i);
            *(broad_add+i) += *(mask_neg+i);
    }  
}

////////////////////////////////////////////////////

void add_another(int*mask, int*mask_neg, int*net_add, int*broad_add, 
int& short_mask, const int& counter)
{ 
  ++short_mask; change_mask(mask, short_mask);
            restart_maskAndBroad(mask, mask_neg, net_add, broad_add);
             std::cout << "Network " << counter << ": "; 
       display_net_br(net_add, broad_add, short_mask);
}



