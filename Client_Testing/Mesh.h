#ifndef MESH_H_
#define MESH_H_



/*�޽��� ���̽� �߻� Ŭ����*/
class CMesh
{
public:
	//CMesh Ŭ������ �����ڿ� �Ҹ��ڸ� �����Ѵ�. 
	CMesh(ID3D11Device *pd3dDevice);
	virtual ~CMesh();

	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);	// ���� �����͸� �������Ѵ�

	void AddRef();
	void Release();

protected:
	ID3D11Buffer *m_pd3dVertexBuffer;	/* ���� ���� �������̽� ������. ���� ������ ����� */
	UINT m_nVertices;	// ���� ������ ���� ����
	UINT m_nStride;		// ���� �ϳ��� ����Ʈ ��
	UINT m_nOffset;		// ������ �����Ͱ� ���� ������ ��� �����ϴ°�
	D3D11_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology;	/* � ������Ƽ�� ���·� ���� �����͸� �����ؾ� �ϴ°�*/


	ID3D11Buffer *m_pd3dIndexBuffer;	/* �ε��� ���� �������̽� ������. �ε��� ������ �����*/
	UINT m_nIndices;	// �ε��� ������ �ε��� ����
	UINT m_nStartIndex;	// ��� �ε������� ����Ͽ� ������ ������ ���ΰ�
	int m_nBaseVertex;	// �� �ε����� ������ �ε���

	ID3D11RasterizerState *m_pd3dRasterizerState;	// �����Ͷ����� ���� ��ü�� ���� �������̽� ������
	virtual void CreateRasterizerState(ID3D11Device *pd3dDevice);	// �����Ͷ����� ���¸� �����Ѵ�

private:
	int m_nReferences;	// �� �޽��� �����ϰ� �ִ� ��ü��
};





/* ������ ������ �޴� �޽��� ���̽� Ŭ���� */
class CMeshIlluminated : public CMesh
{
public:
	CMeshIlluminated(ID3D11Device *pd3dDevice);
	virtual ~CMeshIlluminated();

	virtual void Render(ID3D11DeviceContext *pd3dImmediateDeviceContext);

protected:
	void CalculateVertexNormal(BYTE *pVertices, WORD *pIndices); /* ������ ���� ���͸� ���. ���� �����Ϳ� �ε��� �����͸� ��� */

private:
	void SetTriAngleListVertexNormal(BYTE *pVertices); /* '�ε��� ���۸� ������� �ʴ�' �ﰢ�� ����Ʈ�� ���� ���� ���� ��� */
	void SetAverageVertexNormal(BYTE *pVertices, WORD *pIndices, int nPrimitives, int nOffset, bool bStrip); /* '�ε��� ���۸� ����ϴ�' ��� ������Ƽ�� ������ ���� ����, �� ������ �����ϴ� �ﰢ���� ���� ���͵��� ������� ��� */

	D3DXVECTOR3 CalculateTriAngleNormal(BYTE *pVertices, USHORT nIndex0, USHORT nIndex1, USHORT nIndex2); /* �ﰢ���� �� ������ ����Ͽ� �ﰢ���� ���� ���͸� ��� */
};





class CCubeMeshIlluminatedTextured : public CMeshIlluminated
{
public:
	CCubeMeshIlluminatedTextured(ID3D11Device *pd3dDevice, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);
	virtual ~CCubeMeshIlluminatedTextured();

	virtual void SetRasterizerState(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
};



#endif