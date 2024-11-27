#include "pch.h"
#include "Banco.h"
#include "random"
Banco::Banco()
{
	std::random_device rd; // Sinh s? ng?u nhiên th?c s? (n?u có)
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<> dist(0, 9);
	control = 0;
	
	int xm = 50, ym = 50; // toa do ban co
	int d = 40;//kich thuoc ban co
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			mang[i][j].setHcn(xm + j * d, ym + i * d, xm + j * d + d, ym + i * d + d);
		}
	}
	
	int dem1 = 0;
	int rani1 = 0, ranj1 = 0;
	while (dem1 < 9)
	{
		rani1 = dist(gen);
		ranj1 = dist(gen);
		
		if (isDatSo(rani1, ranj1, mang[rani1][ranj1].so) == false)
		{
			
			if (mang[rani1][ranj1].so == 1) {
				mang[rani1][ranj1].bcolor = 1;
			}
			
			dem1++;
			
			ngauNhien();
			
		}
	}
	
	
}

void Banco::draw(CClientDC* dc)
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			mang[i][j].draw(dc);
			//mang[i][j].bcolor = 1;
		}
	}
	
}

void Banco::draw(CPaintDC* dc)
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if(mang[i][j].so == NULL)
				mang[i][j].bcolor = 3; // Màu trắng
				mang[i][j].draw(dc);
			
			//mang[i][j].draw(dc);
			//mang[i][j].bcolor = 1;
		}
	}
}

bool Banco::isDatSo(int mi, int mj, int num)
{
	//ktra hang
	for (int x = 0; x < 9; x++) {
		if (x!=mj && mang[mi][x].so == num) {
			return false;
			//mang[mi][x].bcolor = 4;


		}
	}
	//ktra cot
	for (int y = 0; y < 9; y++) {
		if (y!=mi && mang[y][mj].so == num) {
			return false;
		}
	}
	//ktra pham vi 3x3
	int startmi = (mi / 3) * 3;
	int startmj = (mj / 3) * 3;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if ((startmi + x != mi || startmj + y != mj) &&
				mang[startmi + x][startmj + y].so == num) {
				return false;
			}
		}
	}
	return true;
}

void Banco::ngauNhien()
{
	//Notice: Sau day la thuat toan quay lui, hoi kho nen co tham khao
	//dung phong bat

	std::random_device rd; // Sinh s? ng?u nhiên th?c s?
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<> dist(1, 9); // S? t? 1 ??n 9

	// ??t t?t c? các ô ban ??u b?ng 0
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			mang[i][j].so = 0;
			
		}
	}

	// T?o b?ng Sudoku b?ng cách ?i?n s? h?p l?
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int num = dist(gen); // S? ng?u nhiên ban ??u
			int attempts = 0; // ??m s? l?n th? s?

			// Tìm s? h?p l? cho ô hi?n t?i
			while (!isDatSo(i, j, num)) {
				num = dist(gen);
				attempts++;
				if (attempts > 20) {
					// N?u không tìm ???c s? h?p l? sau nhi?u l?n th?, reset hàng
					for (int k = 0; k < 9; k++) {
						mang[i][k].so = 0;
						mang[i][k].bcolor = 3;
					}
					j = -1; // Quay l?i ??u hàng
					break;
				}
			}

			// N?u s? h?p l?, ??t vào b?ng
			if (attempts <= 20) {
				mang[i][j].so = num;
				mang[i][j].dong = 0;
				mang[i][j].bcolor = 1;
			}
		}
	}

	// Xóa ng?u nhiên 40 ô ?? t?o b?ng Sudoku
	std::uniform_int_distribution<> distIndex(0, 8); // Ch? s? hàng và c?t
	int removed = 0;
	while (removed < 40) {
		int x = distIndex(gen);
		int y = distIndex(gen);

		if (mang[x][y].so != 0) { // Ch? xóa n?u ô ?ó ch?a b? xóa
			mang[x][y].so = 0;
			mang[x][y].dong = 1;
			// ?ánh d?u là ô tr?ng
			removed++;
		}
		else {
			mang[x][y].dong = 0;
		}
	}
}
void Banco::showPopup(CPoint p, CWnd* pWnd, int mi, int mj)
{
	
	if (mang[mi][mj].dong != 1 ) {
		return; // Không hiển thị menu nếu không phải ô trống
	}

	CMenu menu;
	menu.CreatePopupMenu();

	// Sắp xếp các mục menu thành 3x3
	int menuId = 1001; // ID bắt đầu từ 1001
	for (int row = 0; row < 3; row++) {
		CMenu subMenu;  // Tạo submenu cho mỗi hàng
		subMenu.CreatePopupMenu();

		// Mỗi hàng có 3 mục
		for (int col = 0; col < 3; col++) {
			int num = row * 3 + col + 1;  // Tính toán số từ 1 đến 9
			CString item;
			item.Format(_T("%d"), num);
			subMenu.AppendMenu(MF_STRING, menuId++, item); // Thêm mục vào submenu với ID duy nhất
		}

		// Thêm submenu vào menu chính
		menu.AppendMenu(MF_POPUP, (UINT_PTR)subMenu.m_hMenu, _T("")); // Đặt menu con vào menu chính
	}

	hoveredRow = mi;
	hoveredCol = mj;

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, pWnd);
}
void Banco::chonSo(int num)
{
	if (hoveredRow >= 0 && hoveredCol >= 0 && mang[hoveredRow][hoveredCol].dong == 1) {
		if (mang[hoveredRow][hoveredCol].bcolor == 1) {
			return;
		}
		mang[hoveredRow][hoveredCol].so = num;
		//mang[hoveredRow][hoveredCol].dong = 0;// Không còn là ô trống
		if (isDatSo(hoveredRow, hoveredCol, num)) {
			mang[hoveredRow][hoveredCol].bcolor = 2;
			//mang[hoveredRow][hoveredCol].so = num;
			//mang[hoveredRow][hoveredCol].dong = 1;
			
		}
		else {
			mang[hoveredRow][hoveredCol].bcolor = 4;
		}
		hoveredRow = -1;
		hoveredCol = -1;
	}
}

