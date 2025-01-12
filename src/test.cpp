/**
  *
  * WMI
  * @author Thomas Sparber (2016)
  *
 **/

#include <iostream>
#include <unistd.h>

#include <wmi.hpp>
#include <wmiclasses.hpp>

using std::cerr;
using std::cout;
using std::endl;
using std::wcout;

using namespace Wmi;

int main(int /*argc*/, char */*args*/[])
{
	try {
		Win32_ComputerSystem computer = retrieveWmi<Win32_ComputerSystem>();
		Win32_ComputerSystemProduct product  = retrieveWmi<Win32_ComputerSystemProduct>();
		SoftwareLicensingService liscense  = retrieveWmi<SoftwareLicensingService>();
		Win32_OperatingSystem os_info  = retrieveWmi<Win32_OperatingSystem>();

		cout<<"Computername: "<<computer.Name<<" Domaind:"<<computer.Domain<<endl;
		cout<<"Product: "<<product.Name<<" UUID:"<<product.UUID<<endl;
		cout<<"Architecture: "<<os_info.OSArchitecture<<std::endl;
		cout<<endl;
                cout << "Machine Id:" << liscense.ClientMachineID << " Kmsid:" << liscense.KeyManagementServiceProductKeyID << std::endl;
                cout<<"Installed services:"<<endl;

		// gets all rows and all columns
		for(const Win32_Service &service : retrieveAllWmi<Win32_Service>())
		{
			cout<<service.Caption<<" started:"<<service.Started<<" state:"<<service.State<<  endl;
		}
		
		// gets all rows and only specified columns(better performance)
		for(const Win32_Service &service : retrieveAllWmi<Win32_Service>("Caption,Started,State"))
		{
			cout<<service.Caption<<" started:"<<service.Started<<" state:"<<service.State<<  endl;
		}
	} catch (const WmiException &ex) {
		cerr<<"Wmi error: "<<ex.errorMessage<<", Code: "<<ex.hexErrorCode()<<endl;
		return 1;
	}

	return 0;
}