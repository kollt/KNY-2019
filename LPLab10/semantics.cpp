#include "stdafx.h"
namespace semantics
{
	void semantics(Lex::LEX lex) {
		bool id = false, RepLet = false, RepFunc = false;
		bool bodyif = false, bodyelse = false;
		bool main = false;
		for (int i = 0; i < lex.lextable.size; i++) {
			if (lex.lextable.table[i].lexema == LEX_ID) {
				if (lex.lextable.table[i - 2].lexema != LEX_DECL && lex.idtable.table[lex.lextable.table[i].idxTI].idtype != IT::P && lex.lextable.table[i - 1].lexema != LEX_FUNCTION) {
					id = false;
					for (int j = 0; j < i; j++) {
						if (lex.lextable.table[j].lexema == LEX_ID) {
							if (!strcmp((const char*)lex.idtable.table[lex.lextable.table[i].idxTI].id, (const char*)lex.idtable.table[lex.lextable.table[j].idxTI].id)) {
								id = true;
								break;
							}
						}
					}
					if (!id) {
						throw ERROR_THROW_IN(612, lex.lextable.table[i].sn);
					}
				}
			}
			else if (lex.lextable.table[i].lexema == LEX_IF) {
				if (bodyif || bodyelse) {
					throw ERROR_THROW_IN(611, lex.lextable.table[i].sn);
				}
				bodyif = true;
				if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].iddatatype != IT::BOOL) {
					throw ERROR_THROW_IN(610, lex.lextable.table[i].sn);
				}
			}
			else if (lex.lextable.table[i].lexema == LEX_ELSE) {
				bodyelse = true;
			}
			else if (lex.lextable.table[i].lexema == LEX_RIGHTWALL) {
				if (bodyif) {
					bodyif = false;
				}
				else {
					bodyelse = false;
				}
			}
			else if (lex.lextable.table[i].lexema == LEX_EQUAL) {
				if (lex.lextable.table[i + 1].lexema == LEX_CONVERT) {
					if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].iddatatype != IT::STRING && lex.idtable.table[lex.lextable.table[i + 2].idxTI].iddatatype != IT::CR) {
						throw ERROR_THROW_IN(606, lex.lextable.table[i].sn);
					}
					if (lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype != IT::UNIC)
						throw ERROR_THROW_IN(613, lex.lextable.table[i].sn);
					if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.len > 1) {
						while (lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[0] == '0') {
							for (int h = 0; h < lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.len; h++)
							{
								lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] = lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h + 1];
							}
							lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.len--;
						}
						for (int h = 0; h < lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.len; h++) {
							if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] != '0' && lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] != '1' && lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] != '2' && lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] != '3' && lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] != '4' && lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] != '5' &&  lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] != '6' && lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] != '7' && lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] != '8' && lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vstr.str[h] != '9') {
								throw ERROR_THROW_IN(630, lex.lextable.table[i].sn);
							}
						}
						}
						continue;
					}
				if (lex.lextable.table[i + 1].lexema == LEX_CMP) {
					if (lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype != IT::BOOL)
						throw ERROR_THROW_IN(613, lex.lextable.table[i].sn);
					int k = i;
					while (lex.lextable.table[k].lexema != LEX_SEMICOLON) {
						if (lex.lextable.table[k].lexema == LEX_ID) {
							switch (lex.idtable.table[lex.lextable.table[k].idxTI].iddatatype)
							{
							case IT::BOOL:
								if (lex.idtable.table[lex.lextable.table[k + 2].idxTI].iddatatype != IT::BOOL) {
									if (lex.idtable.table[lex.lextable.table[k + 2].idxTI].iddatatype != IT::UNIC) {
										throw ERROR_THROW_IN(202, lex.lextable.table[i].sn);
									}
									else if (lex.idtable.table[lex.lextable.table[k + 2].idxTI].value.vint > 1) {
										throw ERROR_THROW_IN(202, lex.lextable.table[i].sn);
									}
								}
								break;
							case IT::CR:
								if (lex.idtable.table[lex.lextable.table[k + 2].idxTI].iddatatype != IT::CR && lex.idtable.table[lex.lextable.table[k + 2].idxTI].iddatatype != IT::STRING) {
										throw ERROR_THROW_IN(202, lex.lextable.table[i].sn);
								}
								break;
							case IT::UNIC:
								if (lex.idtable.table[lex.lextable.table[k + 2].idxTI].iddatatype != IT::UNIC) {
									throw ERROR_THROW_IN(202, lex.lextable.table[i].sn);
								}
								break;
							default:
								break;
							}
							break;
						}
						if (lex.lextable.table[k].lexema == LEX_LITERAL) {
							switch (lex.idtable.table[lex.lextable.table[k].idxTI].iddatatype)
							{
							case IT::STRING:
								if (lex.idtable.table[lex.lextable.table[k + 2].idxTI].iddatatype != IT::STRING && lex.idtable.table[lex.lextable.table[k + 2].idxTI].iddatatype != IT::CR) {
									throw ERROR_THROW_IN(202, lex.lextable.table[i].sn);
								}
								break;
							case IT::UNIC:
								if (lex.idtable.table[lex.lextable.table[k + 2].idxTI].iddatatype != IT::UNIC) {
									throw ERROR_THROW_IN(202, lex.lextable.table[i].sn);
								}
								break;
							default:
								break;
							}
							break;
						}
						k++;
					}
					continue;
				}
					int k = i;
					while (lex.lextable.table[k].lexema != LEX_SEMICOLON) {
						if (lex.lextable.table[k].lexema == LEX_ID) {
							if (lex.idtable.table[lex.lextable.table[k].idxTI].idtype == IT::F) {
								if (lex.lextable.table[k + 1].lexema != LEX_LEFTTHESIS) {
									throw ERROR_THROW_IN(628, lex.lextable.table[k + 1].sn);
								}
								for (int j = 0; j < k; j++) {
									if (lex.lextable.table[j].lexema == LEX_FUNCTION) {
										if (lex.idtable.table[lex.lextable.table[k].idxTI].id == lex.idtable.table[lex.lextable.table[j + 1].idxTI].id) {
											int n = k;
											int m = j + 1;
											int FNum = 0; //количество параметров в функции
											int PNum = 0; //количество параметров в вызываемой функции
											LT::LexTable FBuff = LT::Create(LT_MAXSIZE);
											LT::LexTable PBuff = LT::Create(LT_MAXSIZE);
											while (lex.lextable.table[n].lexema != LEX_RIGHTTHESIS) {
												if (lex.lextable.table[n].lexema == LEX_ID || lex.lextable.table[n].lexema == LEX_LITERAL) {
													PNum++;
													LT::Add(PBuff, lex.lextable.table[n]);
												}
												n++;
											}
											while (lex.lextable.table[m].lexema != LEX_RIGHTTHESIS) {
												if (lex.lextable.table[m].lexema == LEX_ID) {
													FNum++;
													LT::Add(FBuff, lex.lextable.table[m]);
												}
												m++;
											}
											if (PNum != FNum) {
												throw ERROR_THROW_IN(620, lex.lextable.table[i].sn);
											}
											for (int h = 0; h < PNum; h++) {
												switch (lex.idtable.table[FBuff.table[h].idxTI].iddatatype)
												{
												case IT::BOOL:
													if (lex.idtable.table[PBuff.table[h].idxTI].iddatatype != IT::BOOL) {
														throw ERROR_THROW_IN(621, lex.lextable.table[i].sn);
													}
													break;
												case IT::UNIC:
													if (lex.idtable.table[PBuff.table[h].idxTI].iddatatype != IT::UNIC) {
														throw ERROR_THROW_IN(621, lex.lextable.table[i].sn);
													}
													break;
												case IT::CR:
													if (lex.idtable.table[PBuff.table[h].idxTI].iddatatype != IT::CR) {
														if (lex.idtable.table[PBuff.table[h].idxTI].iddatatype == IT::STRING) {
															if (lex.idtable.table[PBuff.table[h].idxTI].value.vstr.len > 1) {
																throw ERROR_THROW_IN(621, lex.lextable.table[i].sn);
															}
														}
														else {
															throw ERROR_THROW_IN(621, lex.lextable.table[i].sn);
														}
													}
													break;
												default:
													break;
												}
											}
										}
									}
								}
							}
						}
						k++;
					}
					switch (lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype)
					{
					case IT::UNIC:
						k = i + 1;
						while (lex.lextable.table[k].lexema != LEX_SEMICOLON) {
							if (lex.lextable.table[k].lexema == LEX_ID || lex.lextable.table[k].lexema == LEX_LITERAL) {
								if (lex.idtable.table[lex.lextable.table[k].idxTI].idtype == IT::F) {
									if (lex.idtable.table[lex.lextable.table[k].idxTI].iddatatype != IT::UNIC) {
										throw ERROR_THROW_IN(613, lex.lextable.table[i].sn);
									}
									while (lex.lextable.table[k].lexema != LEX_RIGHTTHESIS)
										k++;
								}
								else if (lex.idtable.table[lex.lextable.table[k].idxTI].iddatatype != IT::UNIC) {
									throw ERROR_THROW_IN(613, lex.lextable.table[i].sn);
								}
							}
							k++;
						}
						break;
					case IT::BOOL:
						k = i + 1;
						while (lex.lextable.table[k].lexema != LEX_SEMICOLON) {
							if (lex.lextable.table[k].lexema == LEX_ID || lex.lextable.table[k].lexema == LEX_LITERAL) {
								if (lex.idtable.table[lex.lextable.table[k].idxTI].idtype == IT::F) {
									if (lex.idtable.table[lex.lextable.table[k].idxTI].iddatatype != IT::BOOL) {
										throw ERROR_THROW_IN(613, lex.lextable.table[i].sn);
									}
									while (lex.lextable.table[k].lexema != LEX_RIGHTTHESIS)
										k++;
								}
								else if (lex.lextable.table[k].lexema == LEX_ID || lex.lextable.table[k].lexema == LEX_LITERAL) {
									if (lex.idtable.table[lex.lextable.table[k].idxTI].value.vint < 0 || lex.idtable.table[lex.lextable.table[k].idxTI].value.vint > 1) {
										throw ERROR_THROW_IN(613, lex.lextable.table[i].sn);
									}
								}
								else
									throw ERROR_THROW_IN(614, lex.lextable.table[i].sn);
							}
							else if (lex.lextable.table[k].lexema == LEX_OPERATOR || lex.lextable.table[k].lexema == LEX_NOT)
								throw ERROR_THROW_IN(614, lex.lextable.table[i].sn);
							k++;
						}
						break;
					case IT::CR:
						k = i + 1;
						while (lex.lextable.table[k].lexema != LEX_SEMICOLON) {
							if (lex.lextable.table[k].lexema == LEX_ID || lex.lextable.table[k].lexema == LEX_LITERAL) {
								if (lex.idtable.table[lex.lextable.table[k].idxTI].idtype == IT::F) {
									if (lex.idtable.table[lex.lextable.table[k].idxTI].iddatatype != IT::CR) {
										throw ERROR_THROW_IN(613, lex.lextable.table[i].sn);
									}
									while (lex.lextable.table[k].lexema != LEX_RIGHTTHESIS)
										k++;
								}
								else if (lex.lextable.table[k].lexema == LEX_ID || lex.lextable.table[k].lexema == LEX_LITERAL) {
									if (lex.idtable.table[lex.lextable.table[k].idxTI].iddatatype == IT::CR || lex.idtable.table[lex.lextable.table[k].idxTI].iddatatype == IT::STRING) {
										if (lex.idtable.table[lex.lextable.table[k].idxTI].value.vstr.len > 1) {
											throw ERROR_THROW_IN(613, lex.lextable.table[i].sn);
										}
									}
									else
										throw ERROR_THROW_IN(613, lex.lextable.table[i].sn);
								}
								else
									throw ERROR_THROW_IN(614, lex.lextable.table[i].sn);
							}
							else if (lex.lextable.table[k].lexema == LEX_OPERATOR || lex.lextable.table[k].lexema == LEX_NOT)
								throw ERROR_THROW_IN(614, lex.lextable.table[i].sn);
							k++;
						}
						break;
					default:
						break;
					}
				}
			else if (lex.lextable.table[i].lexema == LEX_DECL) {
				if (bodyif || bodyelse) {
					throw ERROR_THROW_IN(626, lex.lextable.table[i].sn);
				}
				for (int j = 0; j < i; j++) {
					if (lex.lextable.table[j].lexema == LEX_DECL) {
						if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].id == lex.idtable.table[lex.lextable.table[j + 2].idxTI].id) {
							throw ERROR_THROW_IN(615, lex.lextable.table[i].sn);
						}
					}
					else if (lex.lextable.table[j].lexema == LEX_FUNCTION) {
						int k = j;
						while (lex.lextable.table[k].lexema != LEX_RIGHTTHESIS) {
							if (lex.lextable.table[k].lexema == LEX_ID) {
								if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].id == lex.idtable.table[lex.lextable.table[k].idxTI].id) {
									throw ERROR_THROW_IN(615, lex.lextable.table[i].sn);
								}
							}
							k++;
						}
					}
				}
			}
			else if (lex.lextable.table[i].lexema == LEX_FUNCTION) {
				LT::LexTable tmp = LT::Create(LT_MAXSIZE);
				IT::Entry buff = lex.idtable.table[lex.lextable.table[i + 1].idxTI];
				int k = i;
				while (lex.lextable.table[k].lexema != LEX_RT)
					k++;
				tmp = PN::PolishNotation(k + 1, lex.lextable, lex.idtable);
				if (!strcmp((const char*)lex.idtable.table[tmp.table[0].idxTI].id, (const char*)buff.id)) {
					throw ERROR_THROW_IN(619, lex.lextable.table[k].sn);
				}
				else if (buff.iddatatype != lex.idtable.table[tmp.table[0].idxTI].iddatatype) {
					if (buff.iddatatype == IT::BOOL) {
						if (lex.idtable.table[tmp.table[0].idxTI].iddatatype == IT::UNIC) {
							if (lex.idtable.table[tmp.table[0].idxTI].value.vint != 1 && lex.idtable.table[tmp.table[0].idxTI].value.vint != 0) {
								throw ERROR_THROW_IN(608, lex.lextable.table[k].sn);
							}
						}
						else {
							throw ERROR_THROW_IN(608, lex.lextable.table[k].sn);
						}
					}
					else if (buff.iddatatype == IT::CR) {
						if (lex.idtable.table[tmp.table[0].idxTI].iddatatype == IT::STRING) {
							if (lex.idtable.table[tmp.table[0].idxTI].value.vstr.len > 1) {
								throw ERROR_THROW_IN(608, lex.lextable.table[k].sn);
							}
						}
						else
							throw ERROR_THROW_IN(608, lex.lextable.table[k].sn);
					}
					else
						throw ERROR_THROW_IN(608, lex.lextable.table[k].sn);
				}
			}
			else if (lex.lextable.table[i].lexema == LEX_GENL) {
				if (!main)
					main = true;
				else
					throw ERROR_THROW_IN(622, lex.lextable.table[i].sn);
			}
			else if (lex.lextable.table[i].lexema == LEX_RT) {
				if (main)
					throw ERROR_THROW_IN(623, lex.lextable.table[i].sn);
			}
		}
			if (!main) {
				throw ERROR_THROW_IN(627, lex.lextable.table[lex.lextable.size - 1].sn);
			}
		}
	}