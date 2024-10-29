#ifndef FUNC2_H
#define FUNC2_H

//*mask, *mask_neg, *net_add, *broad_add, user_Response, short_mask
void network_division(int*, int*, int*, int*, const int&, int&);

//*mask, *mask_neg, *net_add, *broad_add
void restart_maskAndBroad(int*, int*, int*, int*);

//*net_add, *broad_add, *mask_neg
void new_network(int*, int*, int*);

//*mask, *mask_neg, *net_add, *broad_add, short_mask, meter
void add_another(int*, int*, int*, int*, int&, const int&);

//mask, mask_neg, ip, net_add, broad_add, short_mask, control
void provide_mask(int*, int*, int*, int*, int*, int&, int&);

//*net_add, *broad_add, short_mask
void display_net_br(const int*, const int*, const int&);

//curent_shortMask, user_Response
const bool compare_shortMask(int&, const int&);

//*mask, short_mask
void change_mask(int*, const int&);

//short_mask
void display_correct_quantity(const int&);


#endif