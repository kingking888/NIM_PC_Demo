﻿#pragma once

#include "base/memory/singleton.h"
#include "login_db.h"

enum LoginStatus
{
	LoginStatus_NONE,		//初始状态
	LoginStatus_LOGIN,		//正在登录
	LoginStatus_CANCEL,		//取消登录
	LoginStatus_SUCCESS,	//已经登录
	LoginStatus_EXIT		//退出登录
};
namespace nim_comp
{
class LoginManager
{
public:
	SINGLETON_DEFINE(LoginManager);
	
	LoginManager();
	bool IsSelf(const std::string &account);
	void SetAccount(const std::string &account);
	std::string GetAccount();
	bool IsEqual(const std::string& account);
	void SetPassword(const std::string &password);
	std::string GetPassword();
	void SetLoginStatus(LoginStatus status);
	LoginStatus GetLoginStatus();
	//断网重连标记
	void SetLinkActive(bool active);
	bool IsLinkActive();

	void SaveLoginData();
	LoginData* GetLoginData()
	{
		return current_login_data_.get();
	}

	void SetDemoLogLevel(int level) { demo_log_level_ = (LOG_LEVEL)level; }
	LOG_LEVEL GetDemoLogLevel() { return demo_log_level_; }

	void SetFileSizeLimit(int file_size) { limit_file_size_ = file_size; }
	int GetFileSizeLimit() { return limit_file_size_; }

private:
	void ReadLoginDataFromFile();
	void ReadDemoLogLevel();

private:
	std::string account_;
	std::string password_;
	LoginStatus status_;
	bool active_;
	std::unique_ptr<LoginData>	current_login_data_;
	UTF8String			default_login_account_;     // 注销跳转到登录view的时候用到

	LOG_LEVEL demo_log_level_ = LV_APP;
	int limit_file_size_ = 15;
};
}