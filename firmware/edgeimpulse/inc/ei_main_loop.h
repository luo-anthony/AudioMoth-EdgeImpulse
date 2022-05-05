// Header file for ei_main_loop. Only contains declaration of main EI method

#ifdef __cplusplus
extern "C"
{
#endif

    float ei_classify(int16_t *raw_features, int signal_size);

    void makeProbArray();
    void printProbArray();
    float *getProbArray();

#ifdef __cplusplus
}
#endif