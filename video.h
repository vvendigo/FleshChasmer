#include <types.h>
//global
extern Uint8 movie_num_layers[16],movie_layer_nodes[16][8],movie_control_nodes[16],movie_type[16];
extern Uint16 movie_length[16];
extern Sint32 movie_node[16][64][8][6];
extern Uint8 movie_control_node[16][128][3];
extern Uint16 movie_node_pos[16][64][8],movie_control_node_pos[16][128];

//current (for Render)
extern Sint32 c_movie_layer[8][6];
extern Uint32 c_movie_object[8][3];


extern Uint8 movie_playing;

extern Uint16 c_movie_step;
extern void MovieStep(void);

extern void ProcMovie(void);

extern void ClearMovie(void);

extern void PlayMovie(Uint8 i);
