


//TODO: Test 
//StructuredBuffer<float> buffer1 : register(t12);//���葤
RWStructuredBuffer<float> inputoutput_b : register(u0); //�󂯎�葤


[numthreads(1, 1, 1)]
void TestCS(uint3 gID : SV_GroupID)
{
    //���L�f�[�^�ɔz��ԍ�������(0~255)
    inputoutput_b[gID.x] = gID.x;
}