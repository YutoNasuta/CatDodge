//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2024/06/09
// <file>			BehaviorNode.h
// <概要>		　　ビヘイビアツリー作成用 ノードライブラリ
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
	/// ノード　インターフェース
	/// </summary>
	class IBehaviorNode
	{
	public:
		virtual ~IBehaviorNode() = default;
		virtual bool Execute() = 0;
	};

	/// <summary>
	/// シーケンスノード
	/// </summary>
	class SequenceNode : public IBehaviorNode
	{
	public:
		// コンストラクタ
		SequenceNode() = default;

		// 子の追加
		void AddChild(std::unique_ptr<IBehaviorNode> child)
		{
			m_children.push_back(std::move(child));
		}

		// 実行する
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
	/// ランダムなセレクタノード
	/// </summary>
	class RandomSelectorNode : public IBehaviorNode
	{
	public:
		// コンストラクタ
		RandomSelectorNode() = default;

		// 子の追加
		void AddChild(std::unique_ptr<IBehaviorNode> child)
		{
			m_children.push_back(std::move(child));
		}

		// 実行する
		bool Execute() override
		{
			// ランダムの中に何もないならfalseを返す
			if (m_children.empty()) { return false; }

			// ランダムにするための準備
			std::random_device rd;
			std::mt19937 gen(rd());
			// ランダムの最小と最大を設定
			std::uniform_int_distribution<> dis(0, m_children.size() - 1);

			int randomIndex = dis(gen);
			// ランダムに選ばれた実行を返す
			return m_children[randomIndex]->Execute();
		}

	private:
		std::vector<std::unique_ptr<IBehaviorNode>> m_children;
	};

	/// <summary>
	///  条件ノード
	/// </summary>
	class ConditionNode : public IBehaviorNode
	{
	public:
		// コンストラクタ
		ConditionNode(std::function<bool()> function)
			:
			m_conditionFunc(function)
		{
		}

		// 実行する
		bool Execute() override
		{
			return m_conditionFunc();
		}

	private:
		std::function<bool()> m_conditionFunc;
	};

	/// <summary>
	/// アクションノード
	/// </summary>
	class ActionNode : public IBehaviorNode
	{
	public:
		// コンストラクタ
		ActionNode(std::function<bool()> function)
			:
			m_actionFunc(function)
		{
		}
		//実行する
		bool Execute() override
		{
			return m_actionFunc();
		}
	private:
		std::function<bool()> m_actionFunc;
	};

	/// <summary>
	/// 条件付きデコレーターノード
	/// </summary>
	class ConditionDecoratorNode : public IBehaviorNode
	{
	public:
		// コンストラクタ
		ConditionDecoratorNode(std::function<bool()> condition, std::unique_ptr<IBehaviorNode> node)
			:
			m_conditionFunc(condition),
			m_node(std::move(node))
		{
		}
		// 実行する
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
	/// 条件分岐ノード
	/// </summary>
	class ContitionalBranchNode : public IBehaviorNode
	{
	public:
		// コンストラクタ
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

		// 実行する
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
	/// ノード実行メソッド
	/// </summary>
	class BehaviorTreeExecutor 
	{
	public:
		// コンストラクタ
		BehaviorTreeExecutor(std::unique_ptr<IBehaviorNode> root)
			: behaviorTreeRoot(std::move(root)) {}

		// 実行する
		void Update() {
			if (behaviorTreeRoot) {
				behaviorTreeRoot->Execute();
			}
		}

		// リセットする
		void Reset(std::unique_ptr<IBehaviorNode> newRoot)
		{
			behaviorTreeRoot = std::move(newRoot);
		}

	private:
		std::unique_ptr<IBehaviorNode> behaviorTreeRoot;
	};


	// 文献
	// ビヘイビアツリーの基本
	// https://engineering.linecorp.com/ja/blog/behavior-tree
	// ビヘイビアツリー実装時の動きなど
	// https://edom18.hateblo.jp/entry/2017/08/28/104547

}