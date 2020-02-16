#define LIN 5
#define BEG 2
#define MID 42
#define PAD 40

#define BAR "|/-\\"
#define BAR_SIZE 4
#define BUF_SIZE 10

#define ALB "./blabla/"
#define BLA "Taptap"
#define BLA_SIZE   strlen(BLA)
#define BLA_SIZE_N strlen(BLA) + 1

#define RES    "\033[0m"
#define GRE_FG "\033[1;32m"
#define GRE_BG "\033[1;102m"
#define RED_FG "\033[1;31m"

#define MAX_PSEUDO_SIZE 14
#define MAX_FILES_COUNT 20

enum BOOL {FALSE, TRUE, UNDEF};

struct tap {
	char        caract;
	enum BOOL   status;
	struct tap *tapnxt;
	struct tap *tapbck;
};

struct ply {
	unsigned int score;
	unsigned int progr;
	char *pseudo;
	char *blabla;
};

