from distutils.core import setup, Extension


def main():
    dwh_hashkit_files = [
        "skein/skein.c",
        "skein/skein_block.c",
        "skein/SHA3api_ref.c",
        "fnv512/fnv512.c",
        "fnv512/uint512.c",
        "lsh/sse2/lsh512_sse2.c",
        "lsh/lsh.c",
        "lsh/no_arch/lsh512.c",
        "lsh/avx2/lsh512_avx2.c",
        "lsh/xop/lsh512_xop.c",
        "lsh/ssse3/lsh512_ssse3.c",
        "blake512/blake512.c",
        "lp_hash.c",
        "keccak3/keccak3.c",
        "whirlpool/Whirlpool_constants_T.c",
        "whirlpool/Whirlpool_constants_0.c",
        "whirlpool/Whirlpool_constants.c",
        "whirlpool/Whirlpool.c",
        "streebog/gost3411-2012-core.c",
        "md6/md6_mode.c",
        "md6/md6_compress.c",
        "jh/jh.c",
        "grostl/grostl.c",
        "cubehash/cubehash.c",
        "hashbox.c",
    ]

    setup(
        name="dwh_hashkit",
        version="1.0.0",
        description="Python module to check if an input hashes to the deep web hash",
        author="",
        ext_modules=[
            Extension(
                "dwh_hashkit",
                dwh_hashkit_files + ["module_main.c"],
                extra_link_args=[
                    "-lcrypto",
                    "-lssl",
                ],
            )
        ],
    )


if __name__ == "__main__":
    main()
