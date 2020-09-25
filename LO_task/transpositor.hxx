#ifndef INCO_NIOCS_TEST_INTERCEPTOREXTENSION_HXX
#define INCO_NIOCS_TEST_INTERCEPTOREXTENSION_HXX

#include <iostream>
#include <com/sun/star/task/XAsyncJob.hpp>
#include <com/sun/star/ui/XContextMenuInterceptor.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#include <cppuhelper/implbase2.hxx>
#include <cppuhelper/implbase1.hxx>
#include <osl/mutex.hxx>

#define IMPLEMENTATION_NAME "TableTranspositor"

namespace com {
    namespace sun {
        namespace star {
	        namespace frame {
		        class XFrame;
	        }
            namespace uno {
                class XComponentContext;
            }
	        namespace beans {
		        struct NamedValue;
	        }
	        namespace task {
		        class XJobListener;
	        }
	        namespace ui {
		        enum ContextMenuInterceptorAction;
		        struct ContextMenuExecuteEvent;
	        }
        }
    }
}

class TableTranspositor : public cppu::WeakImplHelper1<::com::sun::star::ui::XContextMenuInterceptor> {
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext > mxContext;
public:
    TableTranspositor(const ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext > &rxContext) : mxContext(rxContext) {
        std::cout << "Create class" << std::endl;
    }
    virtual ::com::sun::star::ui::ContextMenuInterceptorAction SAL_CALL execuation(
	const ::com::sun::star::ui::ContextMenuExecuteEvent& rEvent )
	throw ( ::com::sun::star::uno::RuntimeException ); 
};

#endif
