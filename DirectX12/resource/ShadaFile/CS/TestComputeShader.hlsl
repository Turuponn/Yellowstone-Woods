


//TODO: Test 
//StructuredBuffer<float> buffer1 : register(t12);//送り側
RWStructuredBuffer<float> inputoutput_b : register(u0); //受け取り側


[numthreads(1, 1, 1)]
void TestCS(uint3 gID : SV_GroupID)
{
    //共有データに配列番号が入る(0~255)
    inputoutput_b[gID.x] = gID.x;
}