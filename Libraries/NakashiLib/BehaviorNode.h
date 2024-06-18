//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2024/06/09
// <file>			BehaviorNode.h
// <�T�v>		�@�@�r�w�C�r�A�c���[�쐬�p �m�[�h���C�u����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <random>

namespace NakashiLib
{
	/// <summary>
	/// �m�[�h�@�C���^�[�t�F�[�X
	/// </summary>
	class IBehaviorNode
	{
	public:
		virtual ~IBehaviorNode() = default;
		virtual bool Execute() = 0;
	};

	/// <summary>
	/// �V�[�P���X�m�[�h
	/// </summary>
	class SequenceNode : public IBehaviorNode
	{
	public:
		// �R���X�g���N�^
		SequenceNode() = default;

		// �q�̒ǉ�
		void AddChild(std::unique_ptr<IBehaviorNode> child)
		{
			m_children.push_back(std::move(child));
		}

		// ���s����
		bool Execute() override
		{
			for (auto& child : m_children)
			{
				if (!child->Execute())
				{
					return false;
				}
			}
			return true;
		}

	private:
		std::vector<std::unique_ptr<IBehaviorNode>> m_children;
	};

	/// <summary>
	/// �����_���ȃZ���N�^�m�[�h
	/// </summary>
	class RandomSelectorNode : public IBehaviorNode
	{
	public:
		// �R���X�g���N�^
		RandomSelectorNode() = default;

		// �q�̒ǉ�
		void AddChild(std::unique_ptr<IBehaviorNode> child)
		{
			m_children.push_back(std::move(child));
		}

		// ���s����
		bool Execute() override
		{
			// �����_���̒��ɉ����Ȃ��Ȃ�false��Ԃ�
			if (m_children.empty()) { return false; }

			// �����_���ɂ��邽�߂̏���
			std::random_device rd;
			std::mt19937 gen(rd());
			// �����_���̍ŏ��ƍő��ݒ�
			std::uniform_int_distribution<> dis(0, m_children.size() - 1);

			int randomIndex = dis(gen);
			// �����_���ɑI�΂ꂽ���s��Ԃ�
			return m_children[randomIndex]->Execute();
		}

	private:
		std::vector<std::unique_ptr<IBehaviorNode>> m_children;
	};

	/// <summary>
	///  �����m�[�h
	/// </summary>
	class ConditionNode : public IBehaviorNode
	{
	public:
		// �R���X�g���N�^
		ConditionNode(std::function<bool()> function)
			:
			m_conditionFunc(function)
		{
		}

		// ���s����
		bool Execute() override
		{
			return m_conditionFunc();
		}

	private:
		std::function<bool()> m_conditionFunc;
	};

	/// <summary>
	/// �A�N�V�����m�[�h
	/// </summary>
	class ActionNode : public IBehaviorNode
	{
	public:
		// �R���X�g���N�^
		ActionNode(std::function<bool()> function)
			:
			m_actionFunc(function)
		{
		}
		//���s����
		bool Execute() override
		{
			return m_actionFunc();
		}
	private:
		std::function<bool()> m_actionFunc;
	};

	/// <summary>
	/// �����t���f�R���[�^�[�m�[�h
	/// </summary>
	class ConditionDecoratorNode : public IBehaviorNode
	{
	public:
		// �R���X�g���N�^
		ConditionDecoratorNode(std::function<bool()> condition, std::unique_ptr<IBehaviorNode> node)
			:
			m_conditionFunc(condition),
			m_node(std::move(node))
		{
		}
		// ���s����
		bool Execute() override
		{
			if ((m_conditionFunc()))
			{
				return m_node->Execute();
			}
			return false;
		}

	private:
		std::function<bool()> m_conditionFunc;
		std::unique_ptr<IBehaviorNode> m_node;
	};

	/// <summary>
	/// ��������m�[�h
	/// </summary>
	class ContitionalBranchNode : public IBehaviorNode
	{
	public:
		// �R���X�g���N�^
		ContitionalBranchNode(
			std::function<bool()> condition,
			std::unique_ptr<IBehaviorNode> trueNode,
			std::unique_ptr<IBehaviorNode> falseNode)
			:
			m_conditionFunc(condition),
			m_trueNode(std::move(trueNode)),
			m_falseNode(std::move(falseNode))
		{
		}

		// ���s����
		bool Execute() override
		{
			if (m_conditionFunc()) {
				return m_trueNode->Execute();
			}
			else {
				return m_falseNode->Execute();
			}
		}

	private:
		std::function<bool()> m_conditionFunc;
		std::unique_ptr<IBehaviorNode> m_trueNode;
		std::unique_ptr<IBehaviorNode> m_falseNode;
	};

	/// <summary>
	/// �m�[�h���s���\�b�h
	/// </summary>
	class BehaviorTreeExecutor 
	{
	public:
		// �R���X�g���N�^
		BehaviorTreeExecutor(std::unique_ptr<IBehaviorNode> root)
			: behaviorTreeRoot(std::move(root)) {}

		// ���s����
		void Update() {
			if (behaviorTreeRoot) {
				behaviorTreeRoot->Execute();
			}
		}

		// ���Z�b�g����
		void Reset(std::unique_ptr<IBehaviorNode> newRoot)
		{
			behaviorTreeRoot = std::move(newRoot);
		}

	private:
		std::unique_ptr<IBehaviorNode> behaviorTreeRoot;
	};


	// ����
	// �r�w�C�r�A�c���[�̊�{
	// https://engineering.linecorp.com/ja/blog/behavior-tree
	// �r�w�C�r�A�c���[�������̓����Ȃ�
	// https://edom18.hateblo.jp/entry/2017/08/28/104547

}