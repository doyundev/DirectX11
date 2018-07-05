//==================================================================
//		## ModelLoader ## (assimp ���̺귯���� �̿��� �� ������ �ε��Ѵ�.)
//==================================================================

#pragma once
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>


class ModelLoader
{
public:
	ModelLoader() {};
	~ModelLoader() {};

	//�� ���� �ε�
	SkinModel*	LoadModel(CString path, UINT flag);
	void		LoadAnimation(CString path, SkinModel* model, UINT flag);
protected:
	//��� ���� ����(�� ����)
	void ProcessNode(aiNode* aiNodeInfo, SkinModel* skModel, NodeInfo* parent = NULL, int depth = 0);
	//�޽� ���� ����(��������, �ε��� ����, �⺻ �޽� ����)
	void ProcessMesh(aiMesh* mesh, Vertex& vertices, vector<unsigned long>& indices, vector<HierarchyMesh*>& meshList);
	//���� ���� ����
	void ProcessMaterial(const aiScene* pScene, vector<Material>& matList, CString directoryPath);
	//��Ű�� ���� ����(offset_mat, weight)
	void ProcessSkin(aiMesh* aiMesh, HierarchyMesh* mesh, Vertex& vertices, vector<unsigned long>& indices, SkinModel* skModel);
	//�ִϸ��̼� ���� ����
	void ProcessAnimation(const aiScene* pScene, SkinModel* skModel);

	//�̸��� ���� ��带 ã�´�.
	NodeInfo* FindNode(aiString name, vector<NodeInfo*> nodeList);
};
