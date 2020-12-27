#pragma once

/// <summary>
/// �����������λ����
/// </summary>
/// <param name="input">����λ�������</param>
/// <param name="width">CRCλ��</param>
/// <returns>��λ��������</returns>
template<typename T> T reverseBit(T input, size_t width)
{
    T output = 0;
    for (size_t i = 0; i < width; i++)//����CRCλ��ȷ��ѭ������
    {
        output <<= 1;//��output����ʹ��һ��ѭ����ȷ����λ��Ϊ��λ��ͬʱ�ڱ���ѭ����ȷ��LSB
        if (input & 1)//���ݵ�ǰinput��LSBȷ����ǰoutput��LSB
        {
            output |= 1;
        }
        input >>= 1;//��input�����Ա�����һ��ѭ���л�ȡ��һ����λ
    }
    return output;
}
/// <summary>
/// ֱ�Ӽ���CRCУ��ֵ
/// </summary>
/// <param name="pData">���������ݵ�ͷָ��</param>
/// <param name="length">���������ݳ���</param>
/// <param name="width">CRCλ��</param>
/// <param name="poly">CRC����ʽ</param>
/// <param name="init">�����ʼֵ</param>
/// <param name="refin">�����Ƿ�ת</param>
/// <param name="refout">����Ƿ�ת</param>
/// <param name="xorout">������ֵ</param>
/// <returns>CRCУ��ֵ</returns>
template<typename T> T calculateCrcDirectly(
    unsigned char* pData,
    size_t length,
    size_t width,
    T poly,
    T init,
    bool refin,
    bool refout,
    T xorout)
{
    //��������
    T mask = 0;
    for (size_t i = 0; i < width; i++)
    {
        mask = (mask << 1) | 1;
    }

    T ret = init;
    while (length-- > 0)//�����������ݵ��ֽ������μ���
    {
        if (refin)
        {
            ret ^= reverseBit<T>(*pData++, width);
        }
        else
        {
            ret ^= static_cast<T>(*pData++) << (width - 8);
        }
        for (size_t i = 0; i < 8; i++)//�������ֽڵ�ÿһλ���м���
        {
            if (ret & (static_cast<T>(1) << (width - 1)))//����λ��1��������Ʋ������ʽ����ģ��������������㣩
            {
                ret = ((ret << 1) & mask) ^ poly;
            }
            else//�����������
            {
                ret = ((ret << 1) & mask);
            }
        }
    }
    if (refout)
    {
        return reverseBit<T>(ret ^ xorout, width);
    }
    else
    {
        return ret ^ xorout;
    }
}
/// <summary>
/// ����CRC��ʽ��
/// </summary>
/// <param name="table">CRC��ʽ��ͷָ��</param>
/// <param name="width">CRCλ��</param>
/// <param name="poly">CRC����ʽ</param>
/// <param name="refin">�����Ƿ�ת</param>
/// <param name="refout">����Ƿ�ת</param>
template<typename T> void calculateCrcTable(
    T* table,
    size_t width,
    T poly,
    bool refin,
    bool refout)
{
    for (size_t i = 0; i < 256; i++)
    {
        unsigned char data = static_cast<unsigned char>(i);
        table[i] = calculateCrcDirectly<T>(&data, sizeof(data), width, poly, 0, refin, refout, 0);
    }
}

/// <summary>
/// ����CRCУ��ֵ
/// </summary>
/// <param name="pData">���������ݵ�ͷָ��</param>
/// <param name="length">���������ݳ���</param>
/// <param name="width">CRCλ��</param>
/// <param name="poly">CRC����ʽ</param>
/// <param name="init">�����ʼֵ</param>
/// <param name="refin">�����Ƿ�ת</param>
/// <param name="refout">����Ƿ�ת</param>
/// <param name="xorout">������ֵ</param>
/// <returns>CRCУ��ֵ</returns>
template<typename T> T calculateCrc(
    unsigned char* pData,
    size_t length,
    size_t width,
    T poly,
    T init,
    bool refin,
    bool refout,
    T xorout)
{
    //��������
    T mask = 0;
    for (size_t i = 0; i < width; i++)
    {
        mask = (mask << 1) | 1;
    }

    T table[256];
    calculateCrcTable<T>(table, width, poly, refin, refout);

    T ret = init;
    while (length-- > 0)
    {
        if (refin)
        {
            ret = (ret >> 8) ^ table[(ret ^ *pData++) & 0xff];
        }
        else
        {
            ret = ((ret << 8) & mask) ^ table[(ret >> (width - 8)) ^ *pData++];
        }
    }
    return ret ^ xorout;
}