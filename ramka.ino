const uint8_t SOH = 1;
const uint8_t EOT = 3;
const uint8_t DLE = 16;
const uint8_t modifier = 64;

void  encoding( uint8_t* , uint8_t, uint8_t*, uint8_t);
void decoding( uint8_t* , uint8_t, uint8_t*, uint8_t &);

int main()
 {
     uint8_t input[32];
     uint8_t  data_type;
     uint8_t frame[32]; 
     uint8_t output[32]; 
    
        encoding(input, sizeof(input), frame, 3);
        decoding(frame, sizeof(frame), output, data_type);
        
 }

 void encoding( uint8_t *input_data, uint8_t length_of_data, uint8_t* output_data, uint8_t data_type )    
 {                            
    *output_data = SOH;
    *(output_data+1) = data_type;
    uint8_t number_of_modifications=2;
    for (uint8_t i=0; i<length_of_data; i++){
        if( *(input_data+i)== SOH || *(input_data+i)== EOT || *(input_data+i)== DLE)
        {
            *(output_data + i + number_of_modifications) = DLE;        
            number_of_modifications++;
            *(output_data + i + number_of_modifications) = *(input_data+i)+modifier;
        }
        else
        {
             *(output_data + i + number_of_modifications) = *(input_data+i);
        }
    }
    *(output_data + length_of_data + number_of_modifications+1) = EOT;
    
 }

 void decoding(uint8_t* input_data, uint8_t length_of_data, uint8_t* output_data, uint8_t &data_type )      
 {       
        uint8_t i = 0;      
        while ( *(input_data +i) != SOH){             
            i++;
        } 
        i++;
        data_type =  *(input_data +i++);
        for (uint8_t j = 0; j<length_of_data ; j++)
        {        
            if( *(input_data+i) == DLE)
            {
                i++;
                *(output_data+j) = *(input_data+i) - modifier;
                i ++;
            }
            else if(*(input_data+i) == EOT)
            {
                    break;
            }
            else
            {
                *(output_data + j) = *(input_data+i);
                i++;
            }
        }
 }
