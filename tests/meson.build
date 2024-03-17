nomalloc = environment({'MALLOC_PERTURB_': '0'})

bash = find_program('bash')
testCommands = ['run_test.sh', SDLPoPTester.path(), quickerSDLPoPTester.path() ]
testTimeout = 30

# Tests to run
testSet = [ 
  'lvl01.anyPercent.test',
  'lvl01.pacifist.test',
  'lvl01.100percent.test',
  'lvl02.anyPercent.test',
  'lvl03.anyPercent.test',
]

# Adding tests to the suite
foreach testFile : testSet
  testSuite = testFile.split('.')[0]
  testName = testFile.split('.')[1]
  test(testName,
       bash,
       workdir : meson.current_source_dir(),
       timeout: testTimeout,
       args : [ testCommands, testFile, '--cycleType', 'Full'],
       suite : [ testSuite ])
endforeach