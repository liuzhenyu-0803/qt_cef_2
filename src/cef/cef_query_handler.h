#pragma once

#include <QObject>

#include "include/wrapper/cef_message_router.h"


class CefQueryHandler : public QObject, 
	public CefMessageRouterBrowserSide::Handler
{
	Q_OBJECT

signals:
	void signalQuery();

public:
	explicit CefQueryHandler() {
	}

	virtual bool OnQuery(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int64_t query_id,
		const CefString &request,
		bool persistent,
		CefRefPtr<Callback> callback) override;

	virtual void OnQueryCanceled(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int64_t query_id)  override;

	void callback();

private:
	// �������� query_id �� callback֮���ӳ���ϵ
	std::map<int64_t, CefRefPtr<Callback>> m_pendings;
	CefRefPtr<Callback> callback_;
};
